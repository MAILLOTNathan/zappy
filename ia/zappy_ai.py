#!/usr/bin/python3
import sys
import debug_lib
import os
import subprocess
import threading
import base64

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

    def elevate_parse(self, conn, response):
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
        if response is None:
            exit(84)
        if "Elevation" not in response.decode():
            return response
        if "Elevation" in response.decode():
            response = conn.read_line()
            while response.decode().find("Current") == -1:
                response = self.broadcast_parse(response, conn)
                if 'dead' in response.decode():
                    exit(82)
                if 'ko' in response.decode():
                    return conn.read_line()
                if response.decode().find("Current") != -1:
                    self.level += 1
                    response = conn.read_line()
                    return response
                response = conn.read_line()
            self.level += 1
            return conn.read_line()
        return response

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

    def broadcast_parse(self, response, conn):
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
                data = conn.read_line()
                data = self.broadcast_parse(data, conn)
                return data
            res = response.split('\n')
            self.objectif = {"linemate": res[0].count("linemate"), "deraumere":  res[0].count("deraumere"), "sibur": res[0].count("sibur"), "mendiane": res[0].count("mendiane"), "phiras": res[0].count("phiras"), "thystame": res[0].count("thystame")}
            result = res[0].split(' ')
            self.signal_angle = int(result[1].split(',')[0])
            self.wait = False
            data = conn.read_line()
            data = self.broadcast_parse(data, conn)
            return data
        return response

    def get_food(self, conn):
        """
        Retrieves the amount of food from the inventory command.
        Returns:
            None: If the response is None or 'done'.
            int: The amount of food in the inventory.
        """
        response = conn.send_request('Inventory')
        response = self.broadcast_parse(response, conn)
        response = self.elevate_parse(conn, response)
        if response == None or response == 'done':
            return
        response = response.decode().strip('[]')
        response = response.split(',')
        response = [component.strip() for component in response]
        if "ok" in response:
            return
        if len(response) == 0:
            return
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
        if self.level == 8:
            return
        data = conn.send_request("Incantation")
        if "Elevation" in data.decode():
            data = conn.read_line()
            if data.decode().find('ko') != -1:
                return
            while data.decode().find('Current') == -1:
                data = conn.read_line()
            self.level += 1

    def destroy_random_eggs(self, conn):
        """
        Launches a new instance based on the current state of the agent.

        If the agent's food inventory is less than 10, it launches the `sucide.py` script.
        If the agent's level is 2 and the food inventory is greater than or equal to 10, it launches the `evolver.py` script.
        Otherwise, it launches the `collector.py` script.

        The launched scripts are executed in the background and their output is redirected to os.devnull.
        """
        if conn.conn_num == 1:
            return
        def run_subprocess(command):
            with open(os.devnull, 'w') as devnull:
                process = subprocess.Popen(command, stdout=devnull, stderr=devnull)
                process.wait()
        
        for i in range(0, conn.conn_num):
            command = ["python", "sucide.py", "-p", str(self.port), "-n", self.team_name, "-h", self.host]
            thread = threading.Thread(target=run_subprocess, args=(command,))
            thread.start()

    def stay_alive(self, look, conn):
        """
        Checks if the player is alive and takes necessary actions to stay alive.

        Args:
            look (list): The items in the player's inventory.

        Returns:
            None
        """
        if look == None:
            return
        if look == "done":
            return
        if self.inventory["food"] > 5:
            return
        data = conn.send_request("Take food")
        self.elevate_parse(conn, data)
             
    def crypted_broadcast(self, conn, look):
        """
        Broadcasts the necessary items to the other players.

        Args:
            look (list): The items in the player's inventory.

        Returns:
            None
        """
        if look is None or look == "done":
            return

        team_name_b64 = base64.b64encode(self.team_name.encode()).decode()
        items_string = broadcast_needed(self, look[0][1])
        b64items = base64.b64encode(items_string.encode()).decode()
        concatenated_b64 = team_name_b64 + ":" + b64items
        final_string = "Broadcast " + concatenated_b64
        res = conn.send_request(final_string)
        res = self.broadcast_parse(res, conn)
        return res

    def basic_ia(self, conn):
        """
        Implements the basic logic for the AI behavior.

        Args:
            conn: The connection object used to communicate with the server.

        Returns:
            None
        """
        self.destroy_random_eggs(conn)
        while True:
            print("MOTHER LEVEL IS : ", self.level)
            if self.level == 1:
                for i in range(0,4):
                    if self.level != 1:
                        break
                    self.get_food(conn)
                    res = conn.send_request("Look")
                    res = self.broadcast_parse(res, conn)
                    if self.check_level_up(res) == True:
                        self.do_incantation(conn)
                        continue
                    look = parse_look(res)
                    x,y,nb = get_obj(look, "linemate") if look else (None, None, None)
                    if nb == 0:
                        take_action(self,"food", look, conn)
                    else:
                        take_action(self,"linemate", look, conn)
                    res = conn.send_request("Right")
                    self.broadcast_parse(res, conn)
                res = conn.send_request("Forward")
                self.broadcast_parse(res,conn)
            else:
                res = conn.send_request("Look")
                res = self.broadcast_parse(res, conn)
                res = self.elevate_parse(conn, res)
                look = parse_look(res)
                self.stay_alive(look, conn)
                if self.check_level_up(res) == True:
                    self.do_incantation(conn)
                res = self.crypted_broadcast(conn, look)
                self.elevate_parse(conn, res)
                launch_new_instance(self, look, conn)
                if self.collector >= 1:
                    res = self.crypted_broadcast(conn, look)
                    self.elevate_parse(conn, res)
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
            8: {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
        }
        self.broadcast_key = ""

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
                exit(83)
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

def parse_look(response):
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

def broadcast_needed(bot: TuringAI, tile):
    add = ''
    for i in bot.level_requirements[bot.level]:
        if i != 'player':
            for y in range(bot.level_requirements[bot.level][i]):
                if tile.count(i) < bot.level_requirements[bot.level][i]:
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
        ai.broadcast_parse(res, conn)
    if obj == "linemate":
        return
    for i in range(0, quantity):
        res = conn.send_request("Take " + obj)
        ai.broadcast_parse(res, conn)

def take_action(self, obj, map, conn):
    x,y,nb = get_obj(map, obj)
    if nb <= 0:
        res = conn.send_request("Forward")
        self.broadcast_parse(res, conn)
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
    def run_subprocess(command, callback=None):
        with open(os.devnull, 'w') as devnull:
            process = subprocess.Popen(command, stdout=devnull, stderr=devnull)
            process.wait()
            if callback:
                callback()

    def decrement_collector():
        self.collector -= 1

    if map[0][1].count("food") < 4:
        res = conn.send_request("Fork")
        res = self.broadcast_parse(res, conn)
        self.elevate_parse(conn, res)
        command = ["python", "sucide.py", "-p", str(self.port), "-n", self.team_name, "-h", self.host]
        thread = threading.Thread(target=run_subprocess, args=(command,))
        thread.start()
        return
    if map[0][1].count("player") < 6:
        res = conn.send_request("Fork")
        res = self.broadcast_parse(res, conn)
        self.elevate_parse(conn, res)
        command = ["python", "evolver.py", "-p", str(self.port), "-n", self.team_name, "-h", self.host]
        thread = threading.Thread(target=run_subprocess, args=(command,))
        thread.start()
        return
    if self.collector < 5:
        res = conn.send_request("Fork")
        res = self.broadcast_parse(res, conn)
        self.elevate_parse(conn, res)
        command = ["python", "collector.py", "-p", str(self.port), "-n", self.team_name, "-h", self.host]
        self.collector += 1
        thread = threading.Thread(target=run_subprocess, args=(command, decrement_collector))
        thread.start()
        return

def main():
    """
    This is the main function of the Zappy AI program.
    It is responsible for checking the arguments and executing the necessary logic.
    """
    ai : TuringAI = TuringAI()
    check_args(ai)
    conn = debug_lib.ServerConnection(ai)
    ai.broadcast_key = base64.b64encode(ai.team_name.encode()).decode()
    if ai.debug:
        conn.connect_to_server_debug()
    conn.connect_to_server(ai.team_name)
    ai.basic_ia(conn)

if __name__ == "__main__":
    main()
