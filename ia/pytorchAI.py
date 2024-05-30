#!/usr/bin/python3
import sys
import debug_lib
import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
import random
from collections import deque
import time
import pickle
import os

def help_message():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    exit(0)

def check_args(TuringAI):
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
    if TuringAI.port is None or TuringAI.team_name == "":
        help_message()

def parse_look(response):
    response = response.strip('[]').strip()
    tiles = [tile.strip() for tile in response.split(',') if tile.strip()]
    return tiles

def find_path(direction, conn, object):
    if direction == 0:
        conn.send_request("Take " + object)
    elif direction == 1:
        conn.send_request("Forward")
        conn.send_request("Left")
        conn.send_request("Forward")
        conn.send_request("Take " + object)
    elif direction == 2:
        conn.send_request("Forward")
        conn.send_request("Take " + object)
    elif direction == 3:
        conn.send_request("Forward")
        conn.send_request("Right")
        conn.send_request("Forward")
        conn.send_request("Take " + object)
    elif direction == 4:
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Left")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Take " + object)
    elif direction == 5:
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Left")
        conn.send_request("Forward")
        conn.send_request("Take " + object)
    elif direction == 6:
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Take " + object)
    elif direction == 7:
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Right")
        conn.send_request("Forward")
        conn.send_request("Take " + object)
    elif direction == 8:
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Right")
        conn.send_request("Forward")
        conn.send_request("Forward")
        conn.send_request("Take " + object)

class DQN(nn.Module):
    def __init__(self, input_size, output_size):
        super(DQN, self).__init__()
        self.fc1 = nn.Linear(input_size, 128)
        self.fc2 = nn.Linear(128, 128)
        self.fc3 = nn.Linear(128, output_size)

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        x = torch.relu(self.fc2(x))
        x = self.fc3(x)
        return x

class ReplayMemory:
    def __init__(self, capacity):
        self.capacity = capacity
        self.memory = deque(maxlen=capacity)

    def push(self, transition):
        self.memory.append(transition)

    def sample(self, batch_size):
        return random.sample(self.memory, batch_size)

    def __len__(self):
        return len(self.memory)

class TuringAI:
    def __init__(self):
        self.debug = False
        self.port = None
        self.team_name = ""
        self.host = "localhost"
        self.command = ["Forward", "Right", "Left", "Look", "Inventory", "Broadcast", "Connect_nbr", "Fork", "Eject", "Take food", "Set", "Incantation"]
        self.inventory = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.level = 1

        look_response_example = '[ player, food linemate mendiane, mendiane, food ]'
        state_example = self.compute_state_size(look_response_example, self.inventory)
        self.state_size = len(state_example)
        self.action_size = len(self.command)
        
        self.memory = ReplayMemory(10000)
        self.model = DQN(self.state_size, self.action_size)
        self.target_model = DQN(self.state_size, self.action_size)
        self.optimizer = optim.Adam(self.model.parameters())
        self.criterion = nn.MSELoss()
        self.gamma = 0.99
        self.epsilon = 1.0
        self.epsilon_min = 0.1
        self.epsilon_decay = 0.995

        try:
            self.model.load_state_dict(torch.load("model_weights.pth"))
            self.target_model.load_state_dict(torch.load("model_weights.pth"))
            print("Loaded saved model weights.")
        except FileNotFoundError:
            print("No saved model weights found. Starting from scratch.")

        try:
            with open("replay_memory.pkl", "rb") as f:
                self.memory = pickle.load(f)
            print("Loaded saved replay memory.")
        except FileNotFoundError:
            print("No saved replay memory found. Starting from scratch.")

    def select_action(self, ):
        if random.random() < self.epsilon:
            return random.randrange(self.action_size)
        with torchstate.no_grad():
            return self.model(torch.FloatTensor(state)).argmax().item()

    def train_step(self, batch_size):
        if len(self.memory) < batch_size:
            return
        transitions = self.memory.sample(batch_size)
        batch = list(zip(*transitions))
    
        states = torch.FloatTensor(batch[0])
        actions = torch.LongTensor(batch[1])
        rewards = torch.FloatTensor(batch[2])
        next_states = torch.FloatTensor(batch[3])
        dones = torch.FloatTensor(batch[4])
    
        assert states.shape[1] == self.state_size, f"State size mismatch in training: expected {self.state_size}, got {states.shape[1]}"
    
        q_values = self.model(states).gather(1, actions.unsqueeze(1)).squeeze(1)
        next_q_values = self.target_model(next_states).max(1)[0]
        target_q_values = rewards + self.gamma * next_q_values * (1 - dones)
    
        loss = self.criterion(q_values, target_q_values)
    
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()
    
        if self.epsilon > self.epsilon_min:
            self.epsilon *= self.epsilon_decay

    def update_target_model(self):
        self.target_model.load_state_dict(self.model.state_dict())

    def get_state(self, look_response, inventory):
        tiles = parse_look(look_response)
        food_counts = [tile.count('food') for tile in tiles]
        state = food_counts + list(inventory.values()) + [self.level]
        
        # Debug information
        print(f"Look response: {look_response}")
        print(f"Parsed tiles: {tiles}")
        print(f"Inventory: {inventory}")
        print(f"Generated state: {state}")
        print(f"Expected state size: {self.state_size}, Actual state size: {len(state)}")
        
        return np.array(state, dtype=np.float32)

    def compute_state_size(self, look_response, inventory):
        tiles = parse_look(look_response)
        food_counts = [tile.count('food') for tile in tiles]
        state = food_counts + list(inventory.values()) + [self.level]
        return state

    def check_level_up(self):
        requirements = self.level_requirements[self.level]
        for item in requirements:
            if item == "players":
                continue
            if self.inventory.get(item, 0) < requirements[item]:
                return False
        return True

    def save_progress(self):
        torch.save(self.model.state_dict(), "model_weights.pth")
        with open("replay_memory.pkl", "wb") as f:
            pickle.dump(self.memory, f)
        print("Progress saved.")

def compute_reward(action, result, ai):
    if result == "dead":
        return -100  # Large negative reward for dying
    if action == 3:  # "Look" action
        return 0
    if "Take" in result:  # Successfully taking an item
        if "food" in result:
            return 10  # Reward for taking food
        else:
            return 5  # Reward for taking other items
    if "Incantation" in result and "Elevation underway" in result:
        return 50  # Reward for starting incantation
    if "current level" in result:
        return 100 * ai.level  # Reward for leveling up
    return -1  # Small negative reward for other actions to encourage meaningful actions

def parse_inventory(response):
    items = response.strip('{}').split(',')
    inventory = {}
    for item in items:
        k, v = item.split()
        inventory[k] = int(v)
    return inventory

def basic_ia(conn, ai):
    state = ai.get_state(conn.send_request("Look").decode(), ai.inventory)
    done = False
    while not done and ai.level < 8:
        action = ai.select_action(state)
        
        # Handling actions
        if action == 3:  # Look
            response = conn.send_request("Look")
            direction = parse_look(response.decode())
            find_path(direction, conn, "food")
            result = response.decode()
        elif action == 10:  # Set
            item_to_set = None
            for item, count in ai.inventory.items():
                if count > 0:
                    item_to_set = item
                    break
            if item_to_set:
                result = conn.send_request("Set " + item_to_set).decode()
            else:
                result = "No items to set"
        elif action == 5:  # Broadcast
            message = "Hello team!"
            result = conn.send_request("Broadcast " + message).decode()
        else:
            command = ai.command[action]
            result = conn.send_request(command).decode()

        reward = compute_reward(action, result, ai)
        next_state = ai.get_state(conn.send_request("Look").decode(), ai.inventory)
        done = "dead" in result

        ai.memory.push((state, action, reward, next_state, done))
        state = next_state

        ai.train_step(5)
        ai.update_target_model()

def main():
    ai = TuringAI()
    check_args(ai)
    conn = debug_lib.ServerConnection(ai)
    if ai.debug:
        conn.connect_to_server_debug()
    conn.connect_to_server(ai.team_name)
    basic_ia(conn, ai)

if __name__ == "__main__":
    main()
