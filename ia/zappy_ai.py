#!/usr/bin/python3
import sys
import debug_lib
import os
import subprocess
import threading

class TuringAI:
    """
    Represents an AI agent for the Turing game.

    Attributes:
        debug (bool): Indicates whether debug mode is enabled.
        port (int): The port number for the AI agent to connect to.
        team_name (str): The name of the team the AI agent belongs to.
        machine_name (str): The name of the machine where the game server is running.
        command (list): The list of available commands for the AI agent.
    """
    debug = False
    port = None
    team_name = ""
    host = "localhost"
    food_quantity = 0
    elapsed_time = 0
    inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
    children = 0
    collector = 0

    def check_level_up(self, res):
        """
        Check if the player meets the requirements to level up.

        Args:
        box_zero (list): The items in the player's inventory.

        Returns:
        bool: True if the player meets the requirements, False otherwise.
        """
        if res == None:
            return
        if res == "done":
            return
        res_str = res.decode()
        box_zero = res_str.split(',')[0]
        requirements = self.level_requirements[self.level]
        for item in requirements:
            if box_zero.count(item) < requirements[item]:
                return False
        return True

    def can_fork(self, conn):
        """
        Checks if forking is possible based on the action and result.

        Args:
            conn (Connection): The connection object used to send the request.

        Returns:
            bool: True if forking is possible, False otherwise.
        """
        if conn.conn_num == self.children:
            return False
        return True

    def broadcast_parse(self, response):
        if response == None:
            exit(0)
        if "message" in response.decode():
            response = response.decode()
            self.objectif = {"linemate": response.count("linemate"), "deraumere":  response.count("deraumere"), "sibur": response.count("sibur"), "mendiane": response.count("mendiane"), "phiras": response.count("phiras"), "thystame": response.count("thystame")}
            return self.conn.s.recv(1024)
        return response

    def get_food(self, conn):
        """
        Retrieves the amount of food from the inventory command.
        Returns:
            None: If the response is None or 'done'.
            int: The amount of food in the inventory.
        """
        response = conn.send_request('Inventory')
        response = self.broadcast_parse(response)
        print("smelizieuf")
        if response == None or response == 'done':
            return
        response = response.decode().strip('[]')
        response = response.split(']')[0]
        response = response.split(',')
        response = [component.strip() for component in response]
        response = [int(component.split()[1]) for component in response]
        self.inventory['food'] = response[0]

    def do_incantation(self, conn):
        """
        Perform the incantation action.

        Args:
            None

        Returns:
            None
        """
        data = conn.send_request("Incantation")
        if "Elevation underway" in data.decode():
            self.level += 1
            data = conn.s.recv(1024)

    def update_children(self, conn):
        """
        Updates the number of children based on the number of connections.

        Args:
            None

        Returns:
            None
        """
        try:
            available_conn = conn.send_request("Connect_nbr")
            self.children = conn.conn_num - int(available_conn.decode())
            print("apres con_nb")
        except:
            return

    def basic_ia(self, conn):
        while True:
            if self.level == 1:
                for i in range(0,4):
                    if self.level != 1:
                        break
                    self.get_food(conn)
                    res = conn.send_request("Look")
                    if self.check_level_up(res) == True:
                        self.do_incantation(conn)
                        continue
                    look = parse_look(res, self, "linemate")
                    x,y,nb = get_obj(look, "linemate")
                    if nb == 0:
                        take_action(self,"food", look, conn)
                    else:
                        take_action(self,"linemate", look, conn)
                    conn.send_request("Right")
                conn.send_request("Forward")
            else:
                self.update_children(conn)
                res = conn.send_request("Look")
                look = parse_look(res, self, "food")
                if self.inventory['food'] < 5 and look[0][1].count('food') != 0:
                    res = conn.send_request("Take food")
                elif self.check_level_up(res) == True:
                    self.do_incantation(self, conn)
                elif self.can_fork(conn) == True:
                    launch_new_instance(self, look, conn)
                if self.collector >= 3:
                    conn.s.send(("Broadcast " + broadcast_needed(self)+ "\n").encode())
                self.get_food(conn)

    def __init__(self):
        self.debug = False
        self.port = None
        self.team_name = ""
        self.food_quantity = 0
        self.level = 1
        self.host = "localhost"
        self.elapsed_time = 0
        self.children = 0
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

def parse_look(response, ai, obj):
    """
    Parse the look response from the server and return the tile where there is the most food.

    Args:
        response (str): The response from the server.

    Returns:
        str: The direction where there is the most food.
    """
    response = response.decode()
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

def broadcast_needed(bot: TuringAI):
    add = ''
    for i in bot.level_requirements[bot.level]:
        if i != 'food':
            for y in range(bot.level_requirements[bot.level][i]):
                add += i
    return add
def find_path(direction : list, quantity, obj : str, ai: TuringAI, conn):
    """
    Find the path to the tile with the most food.

    Args:
        direction (str): The direction where there is the most food.

    Returns:
        None
    """
    for i in direction:
        res = conn.send_request(i)
        ai.broadcast_parse(res)
    if obj == "linemate":
        return
    for i in range(0, quantity):
        res = conn.send_request("Take " + obj)
        ai.broadcast_parse(res)

def take_action(self, obj, map, conn):
    x,y,nb = get_obj(map, obj)
    if nb <= 0:
        res = conn.send_request("Forward")
        self.broadcast_parse(res)
        return
    dir = get_direction(x,y)
    find_path(dir, nb, obj, self, conn)

def launch_new_instance(self, map, conn):
    """
    Launches a new instance based on the current state of the agent.

    If the agent's food inventory is less than 10, it launches the `sucide.py` script.
    If the agent's level is 2 and the food inventory is greater than or equal to 10, it launches the `evolver.py` script.
    Otherwise, it launches the `collector.py` script.

    The launched scripts are executed in the background and their output is redirected to os.devnull.
    """
    def run_subprocess(command):
        with open(os.devnull, 'w') as devnull:
            process = subprocess.Popen(command, stdout=devnull, stderr=devnull)
            process.wait()
    if map[0][1].count('food') == 0:
        conn.send_request("Fork")
        command = ["python", "sucide.py", "-p", str(self.port), "-n", self.team_name, "-h", self.host]
        print("made a sucide child")
        thread = threading.Thread(target=run_subprocess, args=(command,))
        thread.start()
    elif map[0][1].count("player") < 4:
        conn.send_request("Fork")
        command = ["python", "evolver.py", "-p", str(self.port), "-n", self.team_name, "-h", self.host]
        print("made an evolver child")
        thread = threading.Thread(target=run_subprocess, args=(command,))
        thread.start()
    elif self.collector < 3:
        conn.send_request("Fork")
        command = ["python", "collector.py", "-p", str(self.port), "-n", self.team_name, "-h", self.host]
        print("made a collector child")
        self.collector += 1
        thread = threading.Thread(target=run_subprocess, args=(command,))
        thread.start()

def main():
    """
    This is the main function of the Zappy AI program.
    It is responsible for checking the arguments and executing the necessary logic.
    """
    ai : TuringAI = TuringAI()
    check_args(ai)
    conn = debug_lib.ServerConnection(ai)
    if ai.debug:
        conn.connect_to_server_debug()
    conn.connect_to_server(ai.team_name)
    ai.basic_ia(conn)

if __name__ == "__main__":
    main()
