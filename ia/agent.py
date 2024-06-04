
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
        self.conn = None
        self.team_name = ""
        self.host = "localhost"
        self.command  = ['Forward', 'Left', 'Right', 'Take food', 'Take linemate', 'Take deraumere', 'Take sibur', 'Take mendiane', 'Take phiras', 'Take thystame', 
                  'Set food', 'Set linemate', 'Set deraumere', 'Set sibur', 'Set mendiane', 'Set phiras', 'Set thystame',
                  'Incantation', 'Fork', 'Eject']
        self.ngames = 0
        self.epsilon = 0
        self.gamma = 0.9
        self.memory = deque(maxlen=MAX_MEMORY)
        self.model = Linear_QNet(618, 1233, 20)
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

    def nb_item(self, looked, item):
        """
        Counts the occurrences of a specific item in a comma-separated string.

        Args:
            looked (str): A comma-separated string containing items.
            item (str): The item to count occurrences of.

        Returns:
            list: A list containing the count of occurrences of the item in each element of the string.
        """
        cut = looked.split(',')
        count = []
        for i in cut:
            count.append(i.count(item))
        return count

    def get_state(self, response):
        """
        Get the state of the agent based on the given response.

        Args:
            response (str): The response received from the agent.

        Returns:
            numpy.ndarray: An array representing the state of the agent.

        """
        if response == 'done':
            return []
        count_comma = response.count(",")
        res = 86 - count_comma
        add_ = ''
        for i in range(res):
            add_ += ','
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
        can_level_up = [self.check_level_up(first_part)]
        state = Food + Linemate + Deraumere + Sibur + Mendiane + Phiras + Thystame + inventory + level + can_level_up
        return np.array(state, dtype=int)

    def check_level_up(self, box_zero):
        """
        Check if the agent can level up based on the items in box_zero.

        Args:
            box_zero (list): The list of items in the agent's possession.

        Returns:
            bool: True if the agent can level up, False otherwise.
        """
        requirements = self.level_requirements[self.level]
        for item in requirements:
            if item == "players":
                continue
            if box_zero.count(item) < requirements[item]:
                return False
        return True
        
    def remember(self, state, action, reward, next_state, done):
        """
        Store the experience tuple (state, action, reward, next_state, done) in the agent's memory.

        Parameters:
        - state: The current state of the environment.
        - action: The action taken by the agent.
        - reward: The reward received from the environment.
        - next_state: The next state of the environment after taking the action.
        - done: A boolean indicating whether the episode is done or not.
        """
        self.memory.append((state, action, reward, next_state, done))

    def train_long_memory(self):
            """
            Trains the agent's long-term memory by sampling a batch of experiences from the memory buffer
            and performing a training step using the trainer.

            If the memory buffer contains more experiences than the batch size, a random sample of size
            BATCH_SIZE is taken. Otherwise, the entire memory buffer is used.

            The experiences are unpacked into separate lists for states, actions, rewards, next states,
            and dones, which are then passed to the trainer's train_step method.

            Args:
                None

            Returns:
                None
            """
            if len(self.memory) > BATCH_SIZE:
                mini_sample = random.sample(self.memory, BATCH_SIZE)
            else:
                mini_sample = self.memory
            states, actions, rewards, next_states, dones = zip(*mini_sample)
            self.trainer.train_step(states, actions, rewards, next_states, dones)

    def train_short_memory(self, state, action, reward, next_state, done):
            """
            Trains the agent's short-term memory by performing a single training step.

            Args:
                state (object): The current state of the environment.
                action (object): The action taken by the agent.
                reward (float): The reward received for taking the action.
                next_state (object): The next state of the environment after taking the action.
                done (bool): Indicates whether the episode has ended.

            Returns:
                None
            """
            self.trainer.train_step(state, action, reward, next_state, done)

    def get_action(self, state):
        """
        Returns the action to be taken by the agent based on the given state.

        Args:
            state (list): The current state of the agent.

        Returns:
            int: The action to be taken by the agent.
        """
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
        """
        Computes the reward based on the final move, result, and elapsed time.

        Args:
            conn (Connection): The connection object used for communication.
            final_move (str): The final move made by the agent.
            result (str): The result of the final move.
            elapsed_time (float): The elapsed time for the final move.

        Returns:
            int: The computed reward value.
        """
        if result == "dead":
            return -20
        if "Incantation" in final_move:
            result = conn.s.recv(1024).decode()
            if "current level" in result:
                return 100 * self.level
        return 0

    def train(self, conn):
        """
        Train the agent using the given connection.

        Parameters:
        - conn: The connection object used to communicate with the game server.

        Returns:
        None
        """
        start_clock = time.time()
        while True:
            res = conn.send_request("Look")
            if res == "done" or res == None:
                self.ngames += 1
                self.train_long_memory()
                self.model.save()
                return
            res = res.decode()
            state_old = self.get_state(res)
            final_move = self.get_action(state_old)
            result = conn.send_request(self.command[final_move])
            elapsed_time = time.time() - start_clock
            reward = self.compute_reward(conn, self.command[final_move], result, elapsed_time)
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