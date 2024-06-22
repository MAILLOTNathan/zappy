#!/usr/bin/python3
import debug_lib
import setup_utils

class Sucide:
    port = None
    team_name = ""
    host = "localhost"
    conn = None
    def __init__(self):
        self.port = None
        self.team_name = ""
        self.host = "localhost"
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.objectif = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.broadcast_key = ""
        self.encrypted_key = ""

    def broadcast_parse(self, response):
        """
        Parses the response received from a broadcast message.

        Args:
            response (bytes): The response received from the server.

        Returns:
            bytes: The encoded response after parsing.

        Raises:
            None

        """
        if response == None:
            exit(0)
        if "message" in response.decode():
            response = response.decode()
            res = response.split('\n')
            print(res)
            if 'message' in res[1]:
                self.objectif = {"linemate": res[1].count("linemate"), "deraumere":  res[1].count("deraumere"), "sibur": res[1].count("sibur"), "mendiane": res[1].count("mendiane"), "phiras": res[1].count("phiras"), "thystame": res[1].count("thystame")}
                result = res[1].split(' ')
                self.signal_angle = int(result[1].split(',')[0])
                self.wait = False
                return res[0].encode()
            else:
                self.objectif = {"linemate": res[0].count("linemate"), "deraumere":  res[0].count("deraumere"), "sibur": res[0].count("sibur"), "mendiane": res[0].count("mendiane"), "phiras": res[0].count("phiras"), "thystame": res[0].count("thystame")}
                result = res[0].split(' ')
                self.signal_angle = int(result[1].split(',')[0])
                self.wait = False
                return self.conn.s.recv(1024)
        return response

    def get_food(self):
        """
        Retrieves the amount of food from the inventory.

        Returns:
            None: If the response is None or 'done'.
            int: The amount of food in the inventory.
        """
        response = self.send_request('Inventory')
        response = self.broadcast_parse(response)
        print(response)
        if response == None or response == 'done':
            return
        response = response.decode().strip('[]')
        response = response.split(',')
        response = [component.strip() for component in response]
        print(response)
        response = [int(component.split()[1]) for component in response]
        self.inventory['food'] = response[0]


    def objectif_done(self):
        """
        Check if the objectives are completed based on the inventory.

        Returns:
            bool: True if the objectives are completed, False otherwise.
        """
        for i in self.inventory:
            if i != 'food' and self.objectif[i] != 0 and self.inventory[i] >= self.objectif[i]:
                return True
        return False

    def get_max_objectif(self):
        """
        Returns the element with the maximum value in the 'objectif' dictionary.

        Returns:
            str: The element with the maximum value in the 'objectif' dictionary.
        """
        max = -1
        element = ''
        for i in self.objectif:
            if self.objectif[i] > max:
                element = i
                max = self.objectif[i]
        return element

    def go_to_broadcast(self):
        """
        Recover a broadcast signal based on the signal angle.

        If the signal angle is 0, it sends a broadcast signal for each food item in the inventory.
        If the signal angle is 1, 3, or 7, it moves forward and sends a broadcast signal.
        If the signal angle is 3 or 4, it turns left and sends a broadcast signal.
        If the signal angle is 7 or 6, it turns right and sends a broadcast signal.
        If the signal angle is 5, it turns right twice and sends a broadcast signal.

        Returns:
            None
        """
        self.wait = True
        if self.signal_angle == 0:
            for i in self.inventory:
                if i == 'food':
                    for y in range(self.inventory[i]):
                        res = self.conn.send_request("Set " + i)
                        self.broadcast_parse(res)
            exit(0)
        if self.signal_angle == 1 or self.signal_angle == 3 or self.signal_angle == 7:
            res = self.conn.send_request("Forward")
            self.broadcast_parse(res)
        elif self.signal_angle == 3 or self.signal_angle == 4:
            res = self.conn.send_request("Left")
            self.broadcast_parse(res)
        elif self.signal_angle == 7 or self.signal_angle == 6:
            res = self.conn.send_request("Right")
            self.broadcast_parse(res)
        elif self.signal_angle == 5:
            res = self.conn.send_request("Right")
            self.broadcast_parse(res)
            res = self.conn.send_request("Right")
            self.broadcast_parse(res)
        return

    def priority_guide(self, map: list):
        """
        Determines the priority action for the agent based on its current state.

        Args:
            map (list): The map representing the game environment.

        Returns:
            None
        """
        if self.inventory['food'] < 3:
            self.take_action('food', map)
        elif self.wait == False:
            self.go_to_broadcast()
        return

    def take_action(self, obj, map):
        """
        Takes an action based on the given object and map.

        Args:
            obj: The object to be processed.
            map: The map containing the object.

        Returns:
            None
        """
        x, y, nb = get_obj(map, obj)
        dir = get_direction(x, y)
        find_path(dir, nb, obj, self)


def parse_look(response):
    """
    Parse the look response from the server and return the tile where there is the most food.

    Args:
        response (str): The response from the server.

    Returns:
        str: The direction where there is the most food.
    """
    tiles = response.strip('[]').split(',')
    if len(tiles) == 1:
        return []
    look = [['',tiles[0],''], [tiles[1],tiles[2],tiles[3]]]
    return look

def get_obj(map, obj):
    """
    Find the coordinates of the most frequent occurrence of a given object in a 2D map.

    Args:
        map (list): A 2D list representing the map.
        obj (str): The object to search for.

    Returns:
        tuple: A tuple containing the x and y coordinates of the most frequent occurrence of the object, 
               and the number of times it occurs.
    """
    x = 0
    y = 0
    nb = 0
    for i in range(len(map)):
        for e in range(len(map[0])):
            if map[i][e].count(obj) > nb:
                x = i
                y = e
                nb = map[i][e].count(obj)
    return x, y, nb

def get_direction(x, y):
    """
    Get the list of directions to move from the current position (x, y).

    Args:
        x (int): The x-coordinate of the current position.
        y (int): The y-coordinate of the current position.

    Returns:
        list: A list of directions to move.

    Example:
        >>> get_direction(3, 2)
        ['Forward', 'Forward', 'Forward', 'Right', 'Forward', 'Forward']
    """
    dir = []
    y -= 1
    for i in range(x):
        dir.append("Forward")
    if y < 0:
        dir.append("Left")
    if y > 0:
        dir.append("Right")
    if abs(y) > 0:
        for i in range(abs(y)):
            dir.append("Forward")
    return dir

def find_path(direction : list, quantity, obj : str, ai ):
    """
    Find the path to the tile with the most food.

    Args:
        direction (str): The direction where there is the most food.

    Returns:
        None
    """
    for i in direction:
        res = ai.conn.send_request(i)
        ai.broadcast_parse(res)
    for i in range(0, quantity):
        res = ai.conn.send_request("Take " + obj)
        print(obj + " taken")
        ai.inventory[obj] += 1
        ai.broadcast_parse(res)

def come_back(direction : list, ia):
    """
    Find the path to the tile with the most food.

    Args:
        direction (str): The direction where there is the most food.

    Returns:
        None
    """
    for i in direction:
        ia.conn.send_request(i)
    for i in range(0, round(ia.inventory["food"] / 3)):
        ia.conn.send_request("Set food")
        ia.inventory["food"] -= 1


def main():
    """
    The main function of the program.
    """
    bot : Sucide = Sucide()
    setup_utils.check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)

    while True:
        response = bot.conn.send_request("Set food")
        if response == None or response == 'done':
            return

if __name__ == "__main__":
    main()