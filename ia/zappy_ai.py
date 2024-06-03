#!/usr/bin/python3
import sys
import debug_lib
import time

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
    level = 1
    elapsed_time = 0
    command ={"Forward": 7, "Right": 7, "Left": 7, "Look": 7, "Inventory": 1, "Broadcast": 7, "Connect_nbr": 0, "Fork": 42, "Eject": 7, "Take": 7, "Set": 7, "Incantation": 300}
    def __init__(self):
        self.debug = False
        self.port = None
        self.team_name = ""
        self.food_quantity = 0
        self.level = 1
        self.host = "localhost"
        self.elapsed_time = 0
        self.command = {"Forward": 7, "Right": 7, "Left": 7, "Look": 7, "Inventory": 1, "Broadcast": 7, "Connect_nbr": 0, "Fork": 42, "Eject": 7, "Take": 7, "Set": 7, "Incantation": 300}
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

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

def parse_look(response, ai, obj):
    """
    Parse the look response from the server and return the tile where there is the most food.

    Args:
        response (str): The response from the server.

    Returns:
        str: The direction where there is the most food.
    """
    print("hereeeee", response)
    print("AI LEVEL", ai.level)
    tiles = response.strip('[]').split(',')
    if len(tiles) == 1:
        return []
    if ai.level == 1:
        look = [['',tiles[0],''], [tiles[1],tiles[2],tiles[3]]]
        return look
    if ai.level == 2:
        look = [['','',tiles[0],'',''], ['',tiles[1],tiles[2],tiles[3],''], [tiles[4],tiles[5],tiles[6],tiles[7],tiles[8]]]
        return look
    if ai.level == 3:
        look = [['','','',tiles[0],'','',''], ['','',tiles[1],tiles[2],tiles[3],'',''], ['',tiles[4],tiles[5],tiles[6],tiles[7],tiles[8],''],
                [tiles[9],tiles[10],tiles[11],tiles[12],tiles[13],tiles[14],tiles[15]]]
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

def get_direction(x,y,ai):
    dir = []
    y -= ai.level
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

def sendRequest(conn, request : str, ai : TuringAI):
    """
    Sends a request to the server and updates the AI's state.

    Args:
        conn (Connection): The connection object used to send the request.
        request (str): The request to be sent to the server.
        ai (TuringAI): The AI object representing the current state of the AI.

    Returns:
        str: The response received from the server.

    Raises:
        None

    """
    res = conn.send_request(request)
    if request == "Incantation":
        return res
    for key in ai.command:
        if key == request:
            ai.elapsed_time += ai.command[key]
    if ai.elapsed_time >= 20:
        ai.elapsed_time = ai.elapsed_time - 20
        ai.inventory["food"] -= 1
    return res

def find_path(direction : list, conn, quantity, obj : str, ai : TuringAI):
    """
    Find the path to the tile with the most food.

    Args:
        direction (str): The direction where there is the most food.

    Returns:
        None
    """
    for i in direction:
        sendRequest(conn, i, ai)
    for i in range(0, quantity):
        sendRequest(conn, "Take " + obj, ai)
        print(obj + " taken")
        ai.inventory[obj] += 1

def basic_ia(ai : TuringAI, conn):
    while True:
        for i in range(0, 4):
            if ai.inventory["linemate"] == 1 and ai.level == 1:
               sendRequest(conn, "Set linemate", ai)
               sendRequest(conn, "Incantation", ai)
               ai.level += 1
               conn.s.recv(1024)
               continue
            sendRequest(conn, "Right", ai)
            response = sendRequest(conn, "Look", ai)
            map = parse_look(response.decode(), ai, 'linemate')
            if len(map) != 0:
                x,y,nb = get_obj(map, "linemate")
                find_path(get_direction(x,y,ai), conn, nb, 'linemate', ai)
            else:
                pass
            map = parse_look(response.decode(), ai, 'food')
            if len(map) == 0:
                continue
            x,y,nb = get_obj(map, "food")
            find_path(get_direction(x,y,ai), conn, nb, 'food', ai)
            ##m_linemate = parse_look_linemate(response.decode(), ai)
            ##if m_linemate != 0:
            ##    find_path(m_linemate, conn, 1, "linemate", ai)
            ##    continue
            ##most_food_case = parse_look(response.decode(), ai)
            ##if most_food_case == '' :
            ##    continue
            ##find_path(most_food_case, conn, ai.food_quantity, "food", ai)
            continue
        sendRequest(conn, "Forward", ai)

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
    basic_ia(ai, conn)

if __name__ == "__main__":
    main()