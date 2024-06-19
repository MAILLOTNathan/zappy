#!/usr/bin/python3
import sys
import debug_lib
import base64
import os
import subprocess
import threading

def help_message():
    """
    Prints the usage message for the zappy_ai script.
    """
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    exit(0)

def check_args(TuringAI):
    """
    Check the command line arguments and perform necessary actions based on the arguments.

    If the number of arguments is less than 2 or the first argument is "-help", it calls the help_message function.
    If the first argument is "--debug", it sets the debug flag to True and sends a debug request.

    Args:
        None

    Returns:
        None
    """
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == "-p":
            TuringAI.port = int(sys.argv[i + 1])
        elif sys.argv[i] == "-n":
            TuringAI.team_name = sys.argv[i + 1]
            if TuringAI.team_name == "GRAPHIC":
                print("Error: Team name cannot be GRAPHIC.")
                exit(84)
        elif sys.argv[i] == "-h":
            TuringAI.host = sys.argv[i + 1]
    if (len(sys.argv) < 2) or sys.argv[1] == "-help":
        help_message()
    if sys.argv[1] == "--debug":
        TuringAI.debug = True
        return
    if TuringAI.port == None or TuringAI.team_name == "":
        help_message()



class evolver:
    debug = False
    port = None
    team_name = ""
    host = "localhost"
    food_quantity = 0
    level = 1
    elapsed_time = 0
    conn = None
    def __init__(self):
        print("EVOLVER INIT")
        self.debug = False
        self.port = None
        self.team_name = ""
        self.food_quantity = 0
        self.level = 1
        self.host = "localhost"
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.level_requirements = {
            1: {"player": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
            2: {"player": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
            3: {"player": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
            4: {"player": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
            5: {"player": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
            6: {"player": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
            7: {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
        }
        self.broadcast_key = None


    def check_level_up(self, box_zero):
        """
        Checks if the player can level up based on the items in their inventory.

        Args:
            box_zero (list): The player's inventory.

        Returns:
            bool: True if the player can level up, False otherwise.
        """
        requirements = self.level_requirements[self.level]
        for item in requirements:
            if box_zero.count(item) < requirements[item]:
                return False
        return True
    
    def elevation_parse(self, response):
        """
        Parses the response received from the server after attempting to elevate the player's level.

        Args:
            conn (connection): The connection object used to communicate with the server.
            response (bytes): The response received from the server.

        Returns:
            bytes: The modified response after parsing.

        Raises:
            SystemExit: If the response is None.

        """
        print("here")
        if response is None:
            exit(84)
        if 'Current level:' in response.decode():
            self.level += 1
            response = self.conn.read_line()
            return response
        if "Elevation" not in response.decode():
            print("not good")
            return response
        if "Elevation" in response.decode():
            print(response.decode())
            response = self.conn.read_line()
            while response.decode().find("Current") == -1:
                response = self.broadcast_parse(response)
                print(response.decode(),'*$*$*$*$')
                if 'dead' in response.decode():
                    exit(84)
                if 'ko' in response.decode():
                    return self.conn.read_line()
                if response.decode().find("Current") != -1:
                    self.level += 1
                    response = self.conn.read_line()
                    return response
                response = self.conn.read_line()
            print("LA DEUXIEME response EST : ", response)
            self.level += 1
            return self.conn.read_line()
        print("LA REPONSEEST : ", response)
        return response

    def do_incantation(self, conn):
        """
        Perform the incantation action.

        Args:
            None

        Returns:
            None
        """
        data = conn.send_request("Incantation")
        if "Elevation" in data.decode():
            print(data.decode(),"-------------")
            data = conn.read_line()
            print(data.decode(), "++++++++++++++++")
            if data.decode().find('ko') != -1:
                return data
            while data.decode().find('Current') == -1:
                data = conn.read_line()
                print(data.decode(), "$$$$$$$$")
                if 'ok' in data.decode():
                    return data
            self.level += 1
            print("test")
        return data

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
            exit(83)
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

def parse_look(response):
    """
    Parse the look response from the server and return the tile where there is the most food.

    Args:
        response (str): The response from the server.

    Returns:
        str: The direction where there is the most food.
    """
    print(response)
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
    return x,y,nb

def get_direction(x,y):
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

def find_path(direction : list, quantity, obj : str, ai ):
    """
    Find the path to the tile with the most food.

    Args:
        direction (str): The direction where there is the most food.

    Returns:
        None
    """
    for i in direction:
        ai.conn.send_request(i)
    for i in range(0, quantity):
        ai.conn.send_request("Take " + obj)
        ai.inventory[obj] += 1

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


def launch_new_instance(self, map, conn):
    """
    Launches a new instance based on the current state of the agent.

    If the agent's food inventory is less than 10, it launches the `sucide.py` script.
    If the agent's level is 2 and the food inventory is greater than or equal to 10, it launches the `evolver.py` script.
    Otherwise, it launches the `collector.py` script.

    The launched scripts are executed in the background and their output is redirected to os.devnull.
    """
    def run_subprocess(command, callback=None):
        with open(os.devnull, 'w') as devnull:
            process = subprocess.Popen(command, stdout=devnull, stderr=devnull)
            process.wait()
            if callback:
                callback()

    if map[0][1].count("food") == 0:
        res = conn.send_request("Fork")
        res = self.broadcast_parse(res)
        self.elevation_parse(res)
        command = ["python", "sucide.py", "-p", str(self.port), "-n", self.team_name, "-h", self.host]
        print("made a sucide child")
        thread = threading.Thread(target=run_subprocess, args=(command,))
        thread.start()
        return

def main():
    bot : evolver = evolver()
    check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)
    bot.broadcast_key = base64.b64encode(bot.team_name.encode()).decode()
    print("Connected to server")
    while True:
        print("level evoler: ", bot.level)
        response = bot.conn.send_request('Look')
        response = bot.broadcast_parse(response)
        response = bot.elevation_parse(response)
        if response == None or response == 'done':
            return
        print(response, 'afer look')
        map = parse_look(response.decode())
        launch_new_instance(bot, map, bot.conn)
        if bot.check_level_up(map[0][1]) == True:
            res = bot.do_incantation(bot.conn)
            res = bot.elevation_parse(res)
            res = bot.broadcast_parse(res)
            print(res, 'incan res')
        response = bot.conn.send_request('Inventory')
        print(response.decode(), "just after")
        response = bot.elevation_parse(response)
        response = bot.broadcast_parse(response)
        response = bot.elevation_parse(response)
        if response == None or response == 'done':
            return
        if 'food' not in response.decode():
            print(response.decode(), 'no food')
            response = bot.conn.read_line()
            response = bot.broadcast_parse(response)
            response = bot.elevation_parse(response)
        print(response.decode(), "invent")
        response = response.decode().strip('[]')
        response = response.split(',')
        response = [component.strip() for component in response]
        response = [int(component.split()[1]) for component in response]
        if response[0] < 5 :
            response = bot.conn.send_request('Take food')
            response = bot.broadcast_parse(response)
            response = bot.elevation_parse(response)

if __name__ == "__main__":
    main()