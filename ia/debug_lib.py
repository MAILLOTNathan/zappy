import sys
import socket

class ServerConnection:
    """
    Represents a connection to the server.

    This class provides methods to establish a connection to the server, send and receive data,
    and handle errors in the connection.

    Attributes:
        HOST (str): The host address of the server.
        PORT (int): The port number of the server.
        s (socket.socket): The socket object used for the connection.
        conn_num (int): The connection number received from the server.

    Methods:
        __init__(self, ai): Initializes a new instance of the ServerConnection class.
        get_con_num(self, data): Extracts the connection number from the received data.
        connect_to_server_debug(self): Connects to the server in debug mode.
        connect_to_server(self, team_name): Connects to the server and sends the team name.
        send_request(self, request): Sends a request to the server and returns the response.
        read_line(self): Reads a line from the server.

    """
    def __init__(self, ai):
        """
        Initializes a new instance of the ServerConnection class.

        Args:
            ai (AI): The AI object containing the host and port information.

        """
        if ai.host == "localhost":
            self.HOST = "127.0.0.1"
        else:
            self.HOST = ai.host
        self.PORT = ai.port
        try :
            self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.s.connect((self.HOST, self.PORT))
            self.conn_num = 0
        except ConnectionRefusedError:
            exit(84)

    def get_con_num(self, data):
        """
        Extracts the connection number from the received data.

        Args:
            data (bytes): The data received from the server.

        Returns:
            None

        """
        res = data.decode().split("\n")
        self.conn_num = int(res[0])

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
        self.get_con_num(data)
        # self.s.sendall(("team2"+ "\n").encode())
        # data = self.s.recv(1024)
        # print(repr(data))
        # data = self.s.recv(1024)
        # print(repr(data))        
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
        self.s.sendall((team_name + "\n").encode())
        data = self.s.recv(1024)
        self.get_con_num(data)
        data = self.s.recv(1024)

    def broad_cast(self,response, bot):
        response = response.decode()
        res = response.split('\n')
        bot.objectif = {"linemate": res[0].count("linemate"), "deraumere":  res[0].count("deraumere"), "sibur": res[0].count("sibur"), "mendiane": res[0].count("mendiane"), "phiras": res[0].count("phiras"), "thystame": res[0].count("thystame")}
        result = res[0].split(' ')
        bot.signal_angle = int(result[1].split(',')[0])
        bot.wait = False
        bot.data = bot.conn.s.recv(1024)

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
            buffer = []
            while True:
                data = self.s.recv(1)
                if not data:
                    break
                if data == b'\n':
                    break
                buffer.append(data)
            data = b''.join(buffer)

            print(repr(data))
            if data == b"dead\n":
                print("AI is dead.")
                return "done"
            return data
        except:
            print("Error: Connection to server lost.")

    def read_line(self):
        """
        Reads a line from the server.

        Returns:
            bytes: The line received from the server.

        """
        buffer = []
        while True:
            data = self.s.recv(1)
            if not data:
                break
            if data == b'\n':
                break
            buffer.append(data)
        data = b''.join(buffer)
        return data
