import sys
import socket
import zappy_ai
import time

class ServerConnection:
    def __init__(self, ai):
        if ai.host == "localhost":
            self.HOST = "127.0.0.1"
        else:
            self.HOST = ai.host
        self.PORT = ai.port
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((self.HOST, self.PORT))

    def connect_to_server_debug(self):
        """
        Connects to the server in debug mode.

        This method establishes a connection to the server and allows the user to send and receive data.
        It continuously listens for user input and sends it to the server. If the user enters "quit",
        the program exits. If there is an error in the connection, an error message is printed and the
        program exits with an exit code of 84.

        Args:
            self: The instance of the class.

        Returns:
            None
        """
        data = self.s.recv(1024)
        print(repr(data))
        while True:
            input = sys.stdin.readline()
            if input == "quit\n":
                exit(0)
            try:
                self.s.send(input.encode())
                data = self.s.recv(1024)
                print(repr(data))
            except:
                print("Error: Connection to server lost.")
                exit(84)

    def connect_to_server(self, team_name):
        """
        Connects to the server and sends the team name.

        Args:
            team_name (str): The name of the team.

        Returns:
            None
        """
        data = self.s.recv(1024)
        print(repr(data))
        self.s.sendall((team_name + "\n").encode())
        data = self.s.recv(1024)
        print(repr(data))
        # data = self.s.recv(1024)
        # print(repr(data))


    def send_request(self, request):
            """
            Sends a request to the server and returns the response.

            Args:
                request (str): The request to send to the server.

            Returns:
                bytes: The response received from the server.

            Raises:
                SystemExit: If there is an error in the connection to the server.
            """
            print("AI request: ", request)
            try:
                self.s.send((request + "\n").encode())
                data = self.s.recv(1024)
                print(repr(data))
                if data == b"dead\n":
                    print("AI is dead.")
                    return "dead"
                return data
            except:
                print("Error: Connection to server lost.")
                exit(84)
