#!/usr/bin/python3
import sys
import debug_lib

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
    command = ["Forward", "Right", "Left", "Look", "Inventory", "Broadcast", "Connect_nbr", "Fork", "Eject", "Take", "Set", "Incantation"]
    def __init__(self):
        self.debug = False
        self.port = None
        self.team_name = ""
        self.host = "localhost"
        self.command = ["Forward", "Right", "Left", "Look", "Inventory", "Broadcast", "Connect_nbr", "Fork", "Eject", "Take", "Set", "Incantation"]
        self.inventory = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

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
    if TuringAI.port == None or TuringAI.team_name == "":
        help_message()

def parse_look(response):
    """
    Parse the look response from the server and return the tile where there is the most food.

    Args:
        response (str): The response from the server.

    Returns:
        str: The direction where there is the most food.
    """
    if 'food' not in response:
        return ''
    tiles = response.strip('[]').split(',')
    food_counts = [tile.count('food') for tile in tiles]
    max_index = food_counts.index(max(food_counts))
    return max_index    

def find_path(direction, conn):
    """
    Find the path to the tile with the most food.

    Args:
        direction (str): The direction where there is the most food.

    Returns:
        None
    """
    if direction == 0:
        print("direction 0")
        conn.send_request("Take food")
        print("Food taken")
    elif direction == 1:
        print("direction 1")
        conn.send_request("Forward")
        conn.send_request("Left")
        conn.send_request("Forward")
        conn.send_request("Take food")
        print("Food taken")
    elif direction == 2:
        print("direction 1")
        conn.send_request("Forward")
        conn.send_request("Take food")
        print("Food taken")
    elif direction == 3:
        print("direction 2")
        conn.send_request("Forward")
        conn.send_request("Right")
        conn.send_request("Forward")
        conn.send_request("Take food")
        print("Food taken")
    elif direction == 4:
        print("direction 3")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Left")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Take food")
        print("Food taken")
    elif direction == 5:
        print("direction 4")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Left")
        conn.send_request("Forward")
        conn.send_request("Take food")
        print("Food taken")
    elif direction == 6:
        print("direction 5")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Take food")
        print("Food taken")
    elif direction == 7:
        print("direction 6")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Right")
        conn.send_request("Forward")
        conn.send_request("Take food")
        print("Food taken")
    elif direction == 8:
        print("direction 7")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Right")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Take food")
        print("Food taken")

def basic_ia(conn):
    while True:
        for i in range(0, 4):
            conn.send_request("Right")
            response = conn.send_request("Look")
            most_food_case = parse_look(response.decode())
            if most_food_case == '' :
                continue
            find_path(most_food_case, conn)
            continue
        conn.send_request("Forward")

def main():
    """
    This is the main function of the Zappy AI program.
    It is responsible for checking the arguments and executing the necessary logic.
    """
    ai = TuringAI()
    check_args(ai)
    conn = debug_lib.ServerConnection(ai)
    if ai.debug:
        conn.connect_to_server_debug()
    conn.connect_to_server(ai.team_name)
    basic_ia(conn)

if __name__ == "__main__":
    main()
