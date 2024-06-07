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
    
    def __init__(self):
        self.debug = False
        self.port = None
        self.team_name = ""
        self.food_quantity = 0
        self.level = 1
        self.signal_angle = [0,0,0,0,0,0,0,0]
        self.host = "localhost"
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.objectif = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

    def broadcast_parse(self, response):
        if response == None:
            exit(0)
        if "message" in response.decode():
            response = response.decode()
            self.objectif = {"linemate": response.count("linemate"), "deraumere":  response.count("deraumere"), "sibur": response.count("sibur"), "mendiane": response.count("mendiane"), "phiras": response.count("phiras"), "thystame": response.count("thystame")}
            for i in range(1,8):
                self.signal_angle[i-1] = response.count(str(i))
            return self.conn.s.recv(1024)
        return response

    def get_food(self):
        response = self.conn.send_request('Inventory')
        response = self.broadcast_parse(response)
        if response == None or response == 'done':
            return
        response = response.decode().strip('[]')
        response = response.split(',')
        response = [component.strip() for component in response]
        response = [int(component.split()[1]) for component in response]
        self.inventory['food'] = response[0]

    def objectif_done(self):
        for i in self.objectif:
            if self.inventory[i] >= self.objectif[i]:
                return False
        return True
    
    def get_max_objectif(self):
        max = -1
        element = ''
        for i in self.objectif:
            if self.objectif[i] > max:
                element = i
                max = self.objectif[i]
        return element
    
    def go_to_broadcast(self):
        if self.signal_angle[0] != 0 and self.signal_angle[2] != 0 and self.signal_angle[5] != 0:
            for i in self.inventory:
                if i != 'food':
                    for i in range(self.inventory[i]):
                        res = self.conn.send_request("Set " + i)
                        self.broadcast_parse(res)
        if self.signal_angle[0] != 0 or self.signal_angle[1] != 0 or self.signal_angle[7] != 0 :
            res = self.conn.send_request("Forward")
            self.broadcast_parse(res)
        elif self.signal_angle[2] != 0 or self.signal_angle[3] != 0:
            res = self.conn.send_request("Left")
            self.broadcast_parse(res)
        elif self.signal_angle[6] != 0 or self.signal_angle[5] != 0:
            res = self.conn.send_request("Right")
            self.broadcast_parse(res)
        elif self.signal_angle[4] != 0:
            res = self.conn.send_request("Right")
            self.broadcast_parse(res)
            res = self.conn.send_request("Right")
            self.broadcast_parse(res)
        return

    def priority_guide(self, map : list): 
        if self.inventory['food'] < 12:
            self.take_action('food', map)
        elif self.objectif_done() == False:
            find = self.get_max_objectif()
            self.take_action(find , map)
        elif self.objectif_done() == True:
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

def find_path(direction : list, quantity, obj : str, ai: food_collector):
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
        ai.broadcast_parse(res)
        print(obj + " taken")
        ai.inventory[obj] = ai.inventory[obj] + 1


def main():
    bot : food_collector = food_collector()
    check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)
    dir = []

    while True:
        for i in range(0, 4):
            response = bot.conn.send_request('Look')
            response = bot.broadcast_parse(response)
            if response == None or response == 'done':
                return
            map = parse_look(response.decode())
            bot.get_food()
            bot.priority_guide(map)
            continue
        bot.conn.send_request('Forward')
        response = bot.broadcast_parse(response)




if __name__ == "__main__":
    main()