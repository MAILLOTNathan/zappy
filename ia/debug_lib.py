import sys
import socket
import zappy_ai

def connect_to_server(HOST, PORT):
    if HOST == "localhost":
        HOST = "127.0.0.1"

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        while True:
            input = sys.stdin.readline()
            if input == "quit\n":
                exit(0)
            try:
                s.send(input.encode())
                data = s.recv(1024)
                print(repr(data))
            except:
                print("Error: Connection to server lost.")
                exit(84)
        
