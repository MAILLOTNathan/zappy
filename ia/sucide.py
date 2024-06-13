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


class Sucide:
    print("COLLECTOR INIT")
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

    def broadcast_parse(self, response):
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
        response = self.send_request('Inventory')
        response = self.broadcast_parse(response)
        print(response)
        if response == None or response == 'done':
            return
        response = response.decode().strip('[]')
        #response = response.split(']')[0]
        response = response.split(',')
        response = [component.strip() for component in response]
        print(response)
        response = [int(component.split()[1]) for component in response]
        self.inventory['food'] = response[0]


    def objectif_done(self):
        for i in self.inventory:
            if i != 'food' and self.objectif[i] != 0 and self.inventory[i] >= self.objectif[i]:
                return True
        return False
    
    def get_max_objectif(self):
        max = -1
        element = ''
        for i in self.objectif:
            if self.objectif[i] > max:
                element = i
                max = self.objectif[i]
        return element
    
    def go_to_broadcast(self):
        self.wait = True
        if self.signal_angle == 0:
            for i in self.inventory:
                if i == 'food':
                    for y in range(self.inventory[i]):
                        res = self.conn.send_request("Set " + i)
                        self.broadcast_parse(res)
            exit(0)
        if self.signal_angle == 1 or self.signal_angle == 3 or self.signal_angle == 7 :
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

    def priority_guide(self, map : list): 
        if self.inventory['food'] < 3:
            self.take_action('food', map)
        elif self.wait == False:
            self.go_to_broadcast()
        return
    
    def take_action(self, obj, map):
        x,y,nb = get_obj(map, obj)
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
    bot : Sucide = Sucide()
    check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)

    while True:
        response = bot.conn.send_request('Inventory')
        if response == None or response == 'done':
            return
        response = response.decode().strip('[]')
        #response = response.split(']')[0]
        response = response.split(',')
        response = [component.strip() for component in response]
        response = [int(component.split()[1]) for component in response]
        for i in range(response[0]):
            bot.conn.send_request("Set food")
    return 0

if __name__ == "__main__":
    main()