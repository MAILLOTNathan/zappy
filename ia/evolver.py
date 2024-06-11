#!/usr/bin/python3
import sys
import debug_lib
import time
import socket


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

    def check_level_up(self, box_zero):
        requirements = self.level_requirements[self.level]
        for item in requirements:
            if box_zero.count(item) < requirements[item]:
                return False
        return True
    
    def elevation_parse(self, response):
        if response is None:
            exit(84)
        if "Elevation" in response.decode():
            response = response.decode()
            res = response.split('\n')
            print(res)
            data = self.conn.read_line()
            while data.decode().find("level") or data.decode().find("ko"):
                data = self.conn.read_line()
                data = self.broadcast_parse(data)
            return data
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
        data = self.broadcast_parse(data)
        if "Elevation underway" in data.decode():
            self.level += 1
            print(data.decode(),"apres inc")
            data = conn.s.recv(1024)
            data = self.broadcast_parse(data)
            return data

    def broadcast_parse(self, response):
        if response == None:
            exit(0)
        if "message" in response.decode():
            response = response.decode()
            res = response.split('\n')
            self.objectif = {"linemate": res[0].count("linemate"), "deraumere":  res[0].count("deraumere"), "sibur": res[0].count("sibur"), "mendiane": res[0].count("mendiane"), "phiras": res[0].count("phiras"), "thystame": res[0].count("thystame")}
            result = res[0].split(' ')
            print("-----------",result)
            self.signal_angle = int(result[1].split(',')[0])
            self.wait = False
            data = self.conn.read_line()
            print(data.decode(),"------------")
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
        print(obj + " taken")
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


def main():
    bot : evolver = evolver()
    check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)

    while True:
        print("EVOLVER LEVEL IS : ", bot.level)
        print("0")
        response = bot.conn.send_request('Look')
        response = bot.broadcast_parse(response)
        print("zzzz")
        response = bot.elevation_parse(response)
        if response == None or response == 'done':
            return
        print("1", response)
        map = parse_look(response.decode())
        print(map)
        print("2")
        if bot.check_level_up(map[0][1]) == True:
            res = bot.do_incantation(bot.conn)
            print(res.decode(), "@@@@@@@@@@@@")
            res = bot.broadcast_parse(res)
            response = bot.elevation_parse(res)
            continue
        print("3")
        response = bot.conn.send_request('Inventory')
        response = bot.broadcast_parse(response)
        response = bot.elevation_parse(response)
        print("4")
        if response == None or response == 'done':
            return
        response = response.decode().strip('[]')
        print(response)
        #response = response.split(']')[0]
        response = response.split(',')
        response = [component.strip() for component in response]
        response = [int(component.split()[1]) for component in response]
        if response[0] < 5 :
            response = bot.conn.send_request('Take food')
            response = bot.broadcast_parse(response)
            response = bot.elevation_parse(response)
    return 0

if __name__ == "__main__":
    main()