#!/usr/bin/python3
import debug_lib
import setup_utils

class Sucide:
    port = None
    team_name = ""
    host = "localhost"
    conn = None
    def __init__(self):
        self.port = None
        self.team_name = ""
        self.host = "localhost"
        self.broadcast_key = ""
        self.encrypted_key = ""

def main():
    """
    The main function of the program.
    """
    bot : Sucide = Sucide()
    setup_utils.check_args(bot)
    bot.conn = debug_lib.ServerConnection(bot)
    bot.conn.connect_to_server(bot.team_name)

    while True:
        response = bot.conn.send_request("Set food")
        if response == None or response == 'done':
            return

if __name__ == "__main__":
    main()