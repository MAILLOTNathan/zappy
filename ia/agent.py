from model import Linear_QNet, QTrainer
from collections import deque
import numpy as np
import random
import torch
import time
import os

MAX_MEMORY = 100_000
BATCH_SIZE = 1000   
LR = 0.010

def generate_sring():
    broadcast = "broadcast "
    string = "abcdefghijklmnopqrstuvwxyz"
    for i in range(10):
        broadcast += random.choice(string)

class TuringAI:
    def __init__(self):
        self.children = False
        self.broadcast_string = generate_sring()
        self.debug = False
        self.port = None
        self.conn = None
        self.team_name = ""
        self.host = "localhost"
        self.command  = ['Forward', 'Left', 'Right', 'Take food', 'Take linemate', 'Take deraumere', 'Take sibur', 'Take mendiane', 'Take phiras', 'Take thystame', 
                  'Set food', 'Set linemate', 'Set deraumere', 'Set sibur', 'Set mendiane', 'Set phiras', 'Set thystame',
                  'Incantation', 'Fork', 'Eject', self.broadcast_string, 'Connect_nbr']
        self.ngames = 0
        self.epsilon = 0
        self.gamma = 0.9
        self.memory = deque(maxlen=MAX_MEMORY)
        self.team_number = 0
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        
        self.model = Linear_QNet(618, 1233, 20).to(self.device)
        self.trainer = QTrainer(self.model, lr=LR, gamma=self.gamma)
        self.level = 1
        self.attempt = 0

        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.level_requirements = {
            1: {"players": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
            2: {"players": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
            3: {"players": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
            4: {"players": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
            5: {"players": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
            6: {"players": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
            7: {"players": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
        }

        try:
            self.model.load()
            print("Model loaded")
            time.sleep(1)
        except:
            print("No model found")
            time.sleep(1)

    def nb_item(self, looked, item):
        cut = looked.split(',')
        count = []
        for i in cut:
            count.append(i.count(item))
        return count

    def get_state(self, response):
        if response == 'done':
            return []

        count_comma = response.count(",")
        res = 86 - count_comma
        add_ = ',' * res
        response = response.replace(']', add_)
        response += ']'
        if len(response) < 10:
            response = '[' + add_ + ']'

        first_part = response.split('[')[0]
        Food = self.nb_item(response, 'food')
        Linemate = self.nb_item(response, 'linemate')
        Deraumere = self.nb_item(response, 'deraumere')
        Sibur = self.nb_item(response, 'sibur')
        Mendiane = self.nb_item(response, 'mendiane')
        Phiras = self.nb_item(response, 'phiras')
        Thystame = self.nb_item(response, 'thystame')
        inventory = [self.inventory['food'], self.inventory["linemate"], self.inventory["deraumere"], self.inventory["sibur"], self.inventory["mendiane"], self.inventory["phiras"], self.inventory["thystame"]]
        level = [self.level]
        can_level_up = [1 if self.check_level_up(first_part) else 0]
        state = Food + Linemate + Deraumere + Sibur + Mendiane + Phiras + Thystame + inventory + level + can_level_up
        return np.array(state, dtype=int)

    def check_level_up(self, box_zero):
        requirements = self.level_requirements[self.level]
        for item in requirements:
            if item == "players":
                continue
            if box_zero.count(item) < requirements[item]:
                return False
        return True
        
    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))

    def train_long_memory(self):
        if len(self.memory) > BATCH_SIZE:
            mini_sample = random.sample(self.memory, BATCH_SIZE)
        else:
            mini_sample = self.memory
        states, actions, rewards, next_states, dones = zip(*mini_sample)
        self.trainer.train_step(states, actions, rewards, next_states, dones)

    def train_short_memory(self, state, action, reward, next_state, done):
        self.trainer.train_step(state, action, reward, next_state, done)

    def get_action(self, state):
        self.epsilon = 80 - self.ngames
        final_move = len(self.command) * [0]
        if random.randint(0, 200) < self.epsilon:
            move = random.randint(0, len(self.command) - 1)
            final_move[move] = 1
        else:
            state0 = torch.tensor(state, dtype=torch.float).to(self.device)
            prediction = self.model(state0)
            move = torch.argmax(prediction).item()
            final_move[move] = 1
        return move

    def compute_reward(self, conn, final_move, result, elapsed_time):
        if final_move is None:
            return 0
        result_str = result.decode("utf-8") if isinstance(result, bytes) else result
        if result_str == "dead":
            return -100
        elif "Incantation" in final_move:
            if "Elevation underway" in result_str:
                print("LEVELING UP")
                time.sleep(1)
                conn.s.recv(1024)
                self.level += 1
                return 100 * self.level
        elif "Take Food" in final_move and "ok" in result_str:
            print("TOOK FOOD")
            time.sleep(1)
            return 12
        elif "Fork" in final_move and "ok" in result_str:
            if self.level == 1:
                return -100
            if self.level > 1:
                return 50
        elif final_move in ['Forward', 'Left', 'Right']:
            return 1
        return 0


    def add_item(self, response, command):
        if response is None:
            return
        if isinstance(response, str) and "done" in response:
            return
        if bytes("ok", "utf-8") in response:
            if "Take" in command:
                self.inventory[command.split(" ")[1]] += 1
            elif "Set" in command and self.inventory[command.split(" ")[1]] > 0:
                self.inventory[command.split(" ")[1]] -= 1

    def save_information(self):
        if self.level >= 2:
            os.makedirs("saved_information", exist_ok=True)
            with open(f"saved_information/LEVELUPinformation_{self.team_name}.txt", "w") as file:
                file.write(f"Team name: {self.team_name}\n")
                file.write(f"Attempt: {self.attempt}\n")
                file.write(f"Games played: {self.ngames}\n")
                file.write(f"Inventory: {self.inventory}\n")
                file.write(f"Level: {self.level}\n")
            return
        file_name = f"information_{self.team_name}.txt"
        os.makedirs("saved_information", exist_ok=True)
        with open(f"saved_information/{file_name}", "w") as file:
            file.write(f"Team name: {self.team_name}\n")
            file.write(f"Attempt: {self.attempt}\n")
            file.write(f"Games played: {self.ngames}\n")
            file.write(f"Inventory: {self.inventory}\n")
            file.write(f"Level: {self.level}\n")

    def launch_new_instance(self):
        print("FORKING NEW INSTANCE")
        if self.inventory["food"] < 10:
            os.system("python pytorchAI -p " + str(self.port) + " -n " + self.team_name + " -w " + "kys" + " -h " + self.host)
        elif self.level == 2 and self.inventory["food"] >= 10:
            os.system("python pytorchAI -p " + str(self.port) + " -n " + self.team_name + " -w " + "evolve" + " -h " + self.host)
        else:
            os.system("python pytorchAI -p " + str(self.port) + " -n " + self.team_name + " -w " + "worker" + " -h " + self.host)

    def can_fork(self, action, result):
        if result is None:
            return False
        result_str = result.decode("utf-8") if isinstance(result, bytes) else result
        if "Fork" in action and "ok" in result_str:
            return True
        return False

    def train(self, conn):
        start_clock = time.time()
        while True:
            res = conn.send_request("Look")
            if res in ("done", None):
                self.train_long_memory()
                self.model.save()
                self.save_information()
                print("DEAD")
                return
            res = res.decode()
            state_old = self.get_state(res)
            final_move = self.get_action(state_old)
            result = conn.send_request(self.command[final_move])
            if self.can_fork(self.command[final_move], result):
                self.launch_new_instance()
            self.add_item(result, self.command[final_move])
            elapsed_time = time.time() - start_clock
            reward = self.compute_reward(conn, self.command[final_move], result, elapsed_time)
            res = conn.send_request("Look")
            if res in ("done", None):
                self.train_long_memory()
                self.model.save()
                self.save_information()
                print("DEAD")
                return
            res = res.decode()
            state_new = self.get_state(res)
            self.train_short_memory(state_old, final_move, reward, state_new, result)
            self.remember(state_old, final_move, reward, state_new, result)
