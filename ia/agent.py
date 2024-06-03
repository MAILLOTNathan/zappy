
from model import Linear_QNet, QTrainer
from collections import deque
import numpy as np
import random
import torch
import time

MAX_MEMORY = 100_000
BATCH_SIZE = 1000   
LR = 0.001

class TuringAI:
    def __init__(self):
        self.debug = False
        self.port = None
        self.team_name = ""
        self.host = "localhost"
        self.command  = ['Forward', 'Left', 'Right', 'Take food', 'Take linemate', 'Take deraumere', 'Take sibur', 'Take mendiane', 'Take phiras', 'Take thystame', 
                  'Set food', 'Set linemate', 'Set deraumere', 'Set sibur', 'Set mendiane', 'Set phiras', 'Set thystame',
                  'Incantation', 'Fork', 'Eject']
        self.ngames = 0
        self.epsilon = 0
        self.gamma = 0.9
        self.memory = deque(maxlen=MAX_MEMORY)
        self.model = Linear_QNet(618, 256, 20)
        self.trainer = QTrainer(self.model, lr=LR, gamma=self.gamma)
        self.level = 1
        
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



    # def start(self):
    #     while True:
    #         state = get_state()
    #         action = get_action()
    #         exec_cmd(action)
    #         save(state,model)

    ## TODO START

    # LEVEL 1 /// b'[ player, linemate thystame,, mendiane ]\n'
    # LEVEL 2 /// b'[ player, food phiras,,, linemate, food, food linemate deraumere, food food, deraumere thystame ]\n'

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
        add_ = ''
        for i in range(res):
            add_ += ','
        response = response.replace(']', add_)
        response += ']'
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
        can_level_up = [self.check_level_up(first_part)]
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
            move = random.randint(0, 2)
            final_move[move] = 1
        else:
            state0 = torch.tensor(state, dtype=torch.float)
            prediction = self.model(state0)
            move = torch.argmax(prediction).item()
            final_move[move] = 1

        return move

    def compute_reward(self, conn, final_move, result, elapsed_time):
        if result == "dead":
            return -20
        print("-----------",result,"----------------")
        if "Incantation" in final_move:
            conn.recv(1024)
            if "current level" in result:
                return 100 * self.level
        return 0

    def train(self, conn):
        start_clock = time.time()
        while True:
            res = conn.send_request("Look")
            if res == "done" or res == None:
                self.ngames += 1
                self.train_long_memory()
                self.model.save()
                return
            print("###############",res,"##############")
            res = res.decode()
            state_old = self.get_state(res)
            final_move = self.get_action(state_old)
            result = conn.send_request(self.command[final_move])
            elapsed_time = time.time() - start_clock
            reward = self.compute_reward(self, self.command[final_move], result, elapsed_time)
            res = conn.send_request("Look")
            if res == "done" or res == None:
                self.ngames += 1
                self.train_long_memory()
                self.model.save()
                return
            res = res.decode()
            state_new = self.get_state(res)
            self.train_short_memory(state_old, final_move, reward, state_new, result)
            self.remember(state_old, final_move, reward, state_new, result)

                

        # while ai.level < 3:
        #     action = ai.select_action(state)
        #     if action == 3:
        #         response = conn.send_request("Look")
        #         map = parse_look(response.decode(), ai, 'food')
        #         if len(map) == 0:
        #             continue
        #         x,y,nb = get_obj(map, "food")
        #         find_path(get_direction(x,y,ai), conn, nb, 'food', ai)
        #     elif action == 9:
        #         if ai.check_level_up():
        #             res = conn.send_request("Incantation")
        #             if res == "dead":
        #                 break
        #             ai.level += 1  # Increment level after successful incantation
        #             reward = 10  # Reward for leveling up
        #             time.sleep(10)
        #         else:
        #             reward = 0
        #     else:
        #         res = conn.send_request(ai.command[action])
        #         if res == "dead":
        #             break
        #         reward = 1 / (time.time() - start_time)  # Default survival reward

        #     try :
        #         next_state = ai.get_state(conn.send_request("Look").decode())
        #     except:
        #         break
        #     done = False

        #     ai.memory.push((state, action, reward, next_state, done))
        #     state = next_state

        #     ai.train_step(32)

        #     if done:
        #         state = ai.get_state(conn.send_request("Look").decode())

        #     ai.update_target_model()

        # print(ai.level)
        # ai.save_progress()