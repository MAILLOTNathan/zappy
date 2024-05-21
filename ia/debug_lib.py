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
        data = self.s.recv(1024)
        print(repr(data))
        self.s.sendall((team_name + "\n").encode())
        data = self.s.recv(1024)
        print(repr(data))         

    def send_request(self, request):
        try:
            self.s.send((request + "\n").encode())
            data = self.s.recv(1024)
            print(repr(data))
            return data
        except:
            print("Error: Connection to server lost.")
            exit(84)