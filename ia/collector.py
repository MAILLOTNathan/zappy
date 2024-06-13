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
    
    def elevate_parse(self, response):
        if response is None:
            exit(84)
        if "Elevation" in response.decode():
            response = response.decode()
            res = response.split('\n')
            print("THE RES IS", res)
            data = self.conn.read_line()
            while data.decode().find("level") >= 0 or data.decode().find("ko") >= 0:
                data = self.conn.read_line()
                data = self.broadcast_parse(data)
                if data.decode().find("level") >= 0:
                    self.level += 1
                    return data
            return data
        return response

    def broadcast_parse(self, response):
        if response == None:
            exit(0)
        if "message" in response.decode():
            response = response.decode()
            res = response.split('\n')
            self.objectif = {"linemate": res[0].count("linemate"), "deraumere":  res[0].count("deraumere"), "sibur": res[0].count("sibur"), "mendiane": res[0].count("mendiane"), "phiras": res[0].count("phiras"), "thystame": res[0].count("thystame")}
            print(res)
            result = res[0].split(' ')
            self.signal_angle = int(result[1].split(',')[0])
            self.wait = False
            data = self.conn.s.recv(1024)
            data = self.broadcast_parse(data)
            return data
        return response

    def get_food(self):
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
        for i in self.inventory:
            if i != 'food' and self.objectif[i] != 0 and self.objectif[i] > self.inventory[i]:
                return False
        return True
    
    def get_max_objectif(self):
        max = -1
        element = ''
        for i in self.objectif:
            if self.objectif[i] > max and self.inventory[i] < self.objectif[i]:
                element = i
                max = self.objectif[i]
        return element
    
    def go_to_broadcast(self):
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
            print("gogogog")
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
        print(obj + " taken")
        ai.inventory[obj] = ai.inventory[obj] + 1

def main():
    a = 0
    bot : food_collector = food_collector()
    check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)

    while True:
        if a == 1:
            response = bot.elevate_parse(response)
        response = bot.conn.send_request('Look')
        response = bot.elevate_parse(response)
        response = bot.broadcast_parse(response)
        response = bot.elevate_parse(response)
        if response == None or response == 'done':
            return
        map = parse_look(response.decode())
        bot.get_food()
        bot.priority_guide(map)
        a = 1

if __name__ == "__main__":
    main()