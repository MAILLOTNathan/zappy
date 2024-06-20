#!/usr/bin/python3
import debug_lib
import setup_utils
import base64

class food_collector:
    debug = False
    port = None
    team_name = ""
    host = "localhost"
    signal_angle = []
    food_quantity = 0
    level = 1
    elapsed_time = 0
    conn = None
    wait = False
    def __init__(self):
        self.debug = False
        self.port = None
        self.team_name = ""
        self.food_quantity = 0
        self.level = 1
        self.signal_angle = -1
        self.wait = True
        self.host = "localhost"
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.objectif = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.broadcast_key = ""
    
    def elevate_parse(self, response):
        """
        Parses the response received after sending an elevation command.

        Args:
            response (bytes): The response received from the server.

        Returns:
            bytes: The parsed response.

        Raises:
            SystemExit: If the response is None.

        """
        if response is None:
            exit(84)
        if "Elevation" not in response.decode():
            return response
        if "Elevation" in response.decode():
            response = self.conn.read_line()
            while response.decode().find("Current") == -1:
                response = self.broadcast_parse(response)
                if 'dead' in response.decode():
                    exit(84)
                if 'ko' in response.decode():
                    return self.conn.read_line()
                if response.decode().find("Current") != -1:
                    self.level += 1
                    response = self.conn.read_line()
                    return response
                response = self.conn.read_line()
            self.level += 1
            return self.conn.read_line()
        return response

    def decrypt_response(self, response):
        """
        Decrypt the response received from the server.

        Args:
            response (str): The response received from the server.

        Returns:
            str: The decrypted response.

        Raises:
            None
        """
        if response.find(self.broadcast_key) == -1:
            return "pass"
        skip_string = self.broadcast_key + ":"
        response = response.split(skip_string)
        decoded_string =  base64.b64decode(response[1].encode()).decode()
        return response[0] + decoded_string

    def broadcast_parse(self, response):
        """
        Parses the response received from a broadcast message.

        Args:
            response (bytes): The response received from the server.

        Returns:
            bytes: The parsed response.

        Raises:
            None

        """
        if response == None:
            exit(0)
        if "message" in response.decode():
            response = self.decrypt_response(response.decode())
            if response == "pass":
                return response
            res = response.split('\n')
            self.objectif = {"linemate": res[0].count("linemate"), "deraumere":  res[0].count("deraumere"), "sibur": res[0].count("sibur"), "mendiane": res[0].count("mendiane"), "phiras": res[0].count("phiras"), "thystame": res[0].count("thystame")}
            result = res[0].split(' ')
            self.signal_angle = int(result[1].split(',')[0])
            self.wait = False
            data = self.conn.read_line()
            data = self.broadcast_parse(data)
            return data
        return response

    def get_food(self):
            """
            Retrieves the food items from the inventory.

            Returns:
                None: If the response is None or 'done'.
            """
            response = self.conn.send_request('Inventory')
            response = self.elevate_parse(response)
            response = self.broadcast_parse(response)
            response = self.elevate_parse(response)
            if response == None or response == 'done':
                return
            response = response.decode().strip('[]')
            response = response.split(',')
            response = [component.strip() for component in response]
            response = [int(component.split()[1]) if len(component.split()) > 1 and component.split()[1].isdigit() else 0 for component in response]
            x = 0
            for i in self.inventory:
                self.inventory[i] = response[x]
                x+=1

    def objectif_done(self):
        """
        Check if the objectives are completed.

        Returns:
            bool: True if all objectives are completed, False otherwise.
        """
        for i in self.inventory:
            if i != 'food' and self.objectif[i] != 0 and self.objectif[i] > self.inventory[i]:
                return False
        return True
    
    def get_max_objectif(self):
        """
        Returns the element with the maximum objective value that has not been reached yet.

        Returns:
            str: The element with the maximum objective value.
        """
        max = -1
        element = ''
        for i in self.objectif:
            if self.objectif[i] > max and self.inventory[i] < self.objectif[i]:
                element = i
                max = self.objectif[i]
        return element
    
    def go_to_broadcast(self):
        """
        Moves the collector to the broadcast location.

        This method is responsible for moving the collector to the broadcast location
        based on the current signal angle. It uses the `conn` object to send requests
        to the server and parses the responses using the `elevate_parse` and `broadcast_parse`
        methods.

        Returns:
            None
        """
        self.wait = True
        if self.signal_angle == 0:
            for i in self.inventory:
                if i != 'food':
                    for y in range(self.inventory[i]):
                        res = self.conn.send_request("Set " + i)
                        res = self.elevate_parse(res)
                        self.broadcast_parse(res)
        if self.signal_angle == 1 or self.signal_angle == 3 or self.signal_angle == 7 :
            res = self.conn.send_request("Forward")
            res = self.elevate_parse(res)
            self.broadcast_parse(res)
        elif self.signal_angle == 3 or self.signal_angle == 4:
            res = self.conn.send_request("Left")
            res = self.elevate_parse(res)
            self.broadcast_parse(res)
        elif self.signal_angle == 7 or self.signal_angle == 6:
            res = self.conn.send_request("Right")
            res = self.elevate_parse(res)
            self.broadcast_parse(res)
        elif self.signal_angle == 5:
            res = self.conn.send_request("Right")
            res = self.elevate_parse(res)
            self.broadcast_parse(res)
            res = self.conn.send_request("Right")
            res = self.elevate_parse(res)
            self.broadcast_parse(res)
        return

    def priority_guide(self, map : list): 
        if self.inventory['food'] < 6:
            self.take_action('food', map)
        elif self.objectif_done() == False:
            find = self.get_max_objectif()
            self.take_action(find , map)
        elif self.objectif_done() == True and self.wait == False:
            self.go_to_broadcast()
        return
    
    def take_action(self, obj, map):
        x,y,nb = get_obj(map, obj)
        if nb == 0:
            res = self.conn.send_request("Forward")
            res = self.elevate_parse(res)
            self.broadcast_parse(res)
            return
        dir = get_direction(x,y)
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
    Find the coordinates and count of the given object in the map.

    Args:
        map (list): A 2D list representing the map.
        obj (str): The object to search for in the map.

    Returns:
        tuple: A tuple containing the x-coordinate, y-coordinate, and count of the object found.
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
                if map[i][e].count('player') > 2:
                    nb = 1
    return x,y,nb

def get_direction(x, y):
    """
    Returns a list of directions based on the given x and y coordinates.

    Args:
        x (int): The x coordinate.
        y (int): The y coordinate.

    Returns:
        list: A list of directions.

    Example:
        >>> get_direction(3, -2)
        ['Forward', 'Forward', 'Forward', 'Left', 'Forward', 'Forward']
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

def find_path(direction : list, quantity, obj : str, ai: food_collector):
    """
    Find the path to the tile with the most food.

    Args:
        direction (str): The direction where there is the most food.

    Returns:
        None
    """
    if dir == []:
        res = ai.conn.send_request(i)
        res = ai.elevate_parse(res)
        ai.broadcast_parse(res)
        return
    for i in direction:
        res = ai.conn.send_request(i)
        res = ai.elevate_parse(res)
        ai.broadcast_parse(res)
    for i in range(0, quantity):
        res = ai.conn.send_request("Take " + obj)
        res = ai.elevate_parse(res)
        ai.broadcast_parse(res)
        ai.inventory[obj] = ai.inventory[obj] + 1

def main():
    a = 0
    bot : food_collector = food_collector()
    setup_utils.check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)
    bot.broadcast_key = base64.b64encode(bot.team_name.encode()).decode()
 
    while True:
        response = bot.conn.send_request('Look')
        response = bot.elevate_parse(response)
        response = bot.broadcast_parse(response)
        if response == None or response == 'done':
            return
        map = parse_look(response.decode())
        bot.get_food()
        bot.priority_guide(map)

if __name__ == "__main__":
    main()