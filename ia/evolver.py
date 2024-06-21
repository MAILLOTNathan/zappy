#!/usr/bin/python3
import debug_lib
import base64
import os
import subprocess
import threading
import setup_utils

class evolver:
    """
    The `evolver` class represents a player in the Zappy game that can evolve to higher levels.

    Attributes:
        debug (bool): Indicates whether debug mode is enabled or not.
        port (int): The port number for the connection.
        team_name (str): The name of the player's team.
        host (str): The host address for the connection.
        food_quantity (int): The quantity of food in the player's inventory.
        level (int): The current level of the player.
        elapsed_time (int): The elapsed time since the start of the game.
        conn (connection): The connection object used to communicate with the server.
        inventory (dict): The player's inventory containing the quantity of each item.
        level_requirements (dict): The requirements for each level in order to level up.

    Methods:
        __init__: Initializes the `evolver` object.
        check_level_up: Checks if the player can level up based on the items in their inventory.
        elevation_parse: Parses the response received from the server after attempting to elevate the player's level.
        do_incantation: Performs the incantation action.
        broadcast_parse: Parses the response received from a broadcast message.
    """

    debug = False
    port = None
    team_name = ""
    host = "localhost"
    food_quantity = 0
    level = 1
    elapsed_time = 0
    conn = None

    def __init__(self):
        """
        Initializes the `evolver` object.

        Args:
            None

        Returns:
            None
        """
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
            8: {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
        }
        self.broadcast_key = ""
        self.encrypted_key = ""


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
            response (bytes): The response received from the server.

        Returns:
            bytes: The modified response after parsing.

        Raises:
            SystemExit: If the response is None.

        """
        if response is None:
            exit(84)
        if 'Current level:' in response.decode():
            self.level += 1
            response = self.conn.read_line()
            return response
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
                return data
            while data.decode().find('Current') == -1:
                data = conn.read_line()
                if 'ko' in data.decode():
                    return data
            self.level += 1
        return data
        
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
    tiles = response.strip('[]').split(',')
    if len(tiles) == 1:
        return []
    look = [['',tiles[0],''], [tiles[1],tiles[2],tiles[3]]]
    return look

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
        thread = threading.Thread(target=run_subprocess, args=(command,))
        thread.start()
        return

def main():
    bot : evolver = evolver()
    setup_utils.check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)
    bot.broadcast_key = base64.b64encode(bot.team_name.encode()).decode()
    while True:
        response = bot.conn.send_request('Look')
        response = bot.elevation_parse(response)
        response = bot.broadcast_parse(response)
        response = bot.elevation_parse(response)
        if response == None or response == 'done':
            return
        map = parse_look(response.decode())
        launch_new_instance(bot, map, bot.conn)
        if bot.check_level_up(map[0][1]) == True:
            res = bot.do_incantation(bot.conn)
            response = bot.broadcast_parse(response)
            response = bot.elevation_parse(response)
        response = bot.conn.send_request('Inventory')
        response = bot.elevation_parse(response)
        response = bot.broadcast_parse(response)
        response = bot.elevation_parse(response)
        if response == None or response == 'done':
            return
        if 'food' not in response.decode():
            response = bot.conn.read_line()
            response = bot.broadcast_parse(response)
            response = bot.elevation_parse(response)
        response = response.decode().strip('[]')
        response = response.split(',')
        response = [component.strip() for component in response]
        response = [int(component.split()[1]) for component in response]
        if response[0] < 6:
            response = bot.conn.send_request('Take food')
            response = bot.elevation_parse(response)
            response = bot.broadcast_parse(response)

if __name__ == "__main__":
    main()