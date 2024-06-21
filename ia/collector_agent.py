from model import Linear_QNet, QTrainer
from collections import deque
import numpy as np
import random
import torch
import time
import os

MAX_MEMORY = 100_000
BATCH_SIZE = 1000
LR = 0.001

class TuringAI:
    """
    The TuringAI class represents an AI agent for playing the game Zappy.
    It contains methods for training and making decisions based on the game state.

    Attributes:
        debug (bool): Indicates whether debug mode is enabled.
        port (int): The port number for the Zappy server.
        conn (Connection): The connection object for communicating with the server.
        team_name (str): The name of the team the AI agent belongs to.
        host (str): The hostname or IP address of the Zappy server.
        command (list): The list of available commands that the AI agent can perform.
        ngames (int): The number of games played by the AI agent.
        epsilon (int): The exploration rate for choosing random actions.
        gamma (float): The discount factor for future rewards in the Q-learning algorithm.
        memory (deque): The replay memory for storing past experiences.
        device (torch.device): The device (CPU or GPU) for running the neural network model.
        model (Linear_QNet): The neural network model for Q-learning.
        trainer (QTrainer): The trainer object for updating the model based on experiences.
        level (int): The current level of the AI agent.
        attempt (int): The number of attempts made to reach the next level.
        inventory (dict): The inventory of items held by the AI agent.

    Methods:
        nb_item(looked, item): Counts the number of occurrences of an item in a string.
        get_state(response): Converts the server response into a state representation.
        check_level_up(box_zero): Checks if the AI agent can level up based on the current state.
        remember(state, action, reward, next_state, done): Stores an experience in the replay memory.
        train_long_memory(): Trains the model using experiences from the replay memory.
        train_short_memory(state, action, reward, next_state, done): Trains the model using a single experience.
        get_action(state): Chooses an action to perform based on the current state.
        compute_reward(conn, final_move, result, elapsed_time): Computes the reward for a given action and server response.
        add_item(response, command): Updates the inventory based on the server response and command.
        save_information(): Saves the AI agent's information to a file.
        train(conn): Trains the AI agent by interacting with the Zappy server.
    """
    def __init__(self):
        self.debug = False
        self.port = None
        self.conn = None
        self.team_name = ""
        self.host = "localhost"
        self.command  = ['Forward', 'Left', 'Right', 'Take food', 'Take linemate', 'Take deraumere', 'Take sibur', 'Take mendiane', 'Take phiras', 'Take thystame', 
                  'Set food', 'Set linemate', 'Set deraumere', 'Set sibur', 'Set mendiane', 'Set phiras', 'Set thystame']
        self.ngames = 0
        self.epsilon = 0
        self.gamma = 0.9
        self.memory = deque(maxlen=MAX_MEMORY)

        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        self.model = Linear_QNet(43, 127, 17).to(self.device)
        self.trainer = QTrainer(self.model, lr=LR, gamma=self.gamma)
        self.level = 1
        self.attempt = 0
        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

    def nb_item(self, looked, item):
        """
        Counts the occurrences of a specific item in a comma-separated string.

        Args:
            looked (str): A comma-separated string containing items.
            item (str): The item to count occurrences of.

        Returns:
            list: A list containing the count of occurrences of the item in each substring.

        Example:
            >>> agent = CollectorAgent()
            >>> agent.nb_item("apple,banana,apple,orange", "apple")
            [2, 0, 1, 0]
        """
        cut = looked.split(',')
        count = []
        for i in cut:
            count.append(i.count(item))
        return count

    def get_state(self, response):
        """
        Get the state of the agent based on the response received.

        Parameters:
        - response (str): The response received from the server.

        Returns:
        - numpy.ndarray: The state of the agent, represented as a numpy array.

        The state is determined by parsing the response and counting the number of items in the agent's inventory.
        The response should be in the format: 'done' or '[item1:item1_count][item2:item2_count]...'

        Example:
        If the response is '[food:3][linemate:1][sibur:2]', the state will be [3, 1, 0, 2, 0, 0, 0, 3, 1, 0, 2, 0, 0, 0],
        where the first 7 elements represent the counts of each item type, and the last 7 elements represent the agent's inventory.
        """
        if response == 'done':
            return []

        first_part = response.split('[')[0]
        Food = self.nb_item(response, 'food')
        Linemate = self.nb_item(response, 'linemate')
        Deraumere = self.nb_item(response, 'deraumere')
        Sibur = self.nb_item(response, 'sibur')
        Mendiane = self.nb_item(response, 'mendiane')
        Phiras = self.nb_item(response, 'phiras')
        Thystame = self.nb_item(response, 'thystame')
        inventory = [self.inventory['food'], self.inventory["linemate"], self.inventory["deraumere"], self.inventory["sibur"], self.inventory["mendiane"], self.inventory["phiras"], self.inventory["thystame"]]
        state = Food + Linemate + Deraumere + Sibur + Mendiane + Phiras + Thystame + inventory
        return np.array(state, dtype=int)

    def check_level_up(self, box_zero):
        """
        Checks if the collector agent can level up based on the items in the given box.

        Args:
            box_zero (list): The list of items in the collector agent's box.

        Returns:
            bool: True if the collector agent can level up, False otherwise.
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
        Stores the experience tuple (state, action, reward, next_state, done) in the agent's memory.

        Parameters:
        state (object): The current state of the agent.
        action (object): The action taken by the agent.
        reward (float): The reward received by the agent.
        next_state (object): The next state after taking the action.
        done (bool): Indicates whether the episode is done or not.
        """
        self.memory.append((state, action, reward, next_state, done))

    def train_long_memory(self):
            """
            Trains the agent's long-term memory by sampling a batch of experiences from the memory buffer and performing a training step.

            If the memory buffer contains more experiences than the batch size, a random sample of size BATCH_SIZE is taken. Otherwise, the entire memory buffer is used.

            The sampled experiences are then unpacked into separate lists for states, actions, rewards, next states, and dones. These lists are passed to the trainer's `train_step` method for training.

            Parameters:
            - None

            Returns:
            - None
            """
            if len(self.memory) > BATCH_SIZE:
                mini_sample = random.sample(self.memory, BATCH_SIZE)
            else:
                mini_sample = self.memory
            states, actions, rewards, next_states, dones = zip(*mini_sample)
            self.trainer.train_step(states, actions, rewards, next_states, dones)

    def train_short_memory(self, state, action, reward, next_state, done):
        """
        Trains the agent's short-term memory by passing the state, action, reward, next_state, and done flag to the trainer.

        Parameters:
        state (object): The current state of the agent.
        action (object): The action taken by the agent.
        reward (float): The reward received by the agent.
        next_state (object): The next state of the agent.
        done (bool): A flag indicating if the episode is done.

        Returns:
        None
        """
        self.trainer.train_step(state, action, reward, next_state, done)

    def get_action(self, state):
        """
        Returns the action to be taken by the collector agent based on the given state.

        Args:
            state (list): The current state of the agent.

        Returns:
            int: The index of the action to be taken.

        """
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
        """
        Computes the reward based on the final move, the result, and the elapsed time.

        Args:
            conn (connection): The connection object used for communication.
            final_move (str): The final move made by the agent.
            result (str): The result received from the server.
            elapsed_time (float): The elapsed time for the current move.

        Returns:
            int: The computed reward value.

        """
        if result == "dead":
            return -100
        elif "Incantation" in final_move:
            if bytes("Elevation underway", "utf-8") in result:
                print("LEVELING UP")
                time.sleep(1)
                conn.s.recv(1024)
                self.level += 1
                return 100 * self.level
        elif "Take Food" in final_move and bytes("ok", "utf-8") in result:
            return 12
        elif "Fork" in final_move and bytes("ok", "utf-8") in result:
            if self.level == 1:
                return -100
            if self.level > 1:
                return 50
        elif final_move in ['Forward', 'Left', 'Right']:
            return 1
        return 0

    def add_item(self, response, command):
        """
        Adds or removes an item from the agent's inventory based on the response and command.

        Args:
            response (str or bytes): The response received from the server.
            command (str): The command that was sent to the server.

        Returns:
            None

        """
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
        """
        Save the agent's information to a file.

        If the agent's level is 2, the information is saved in a file named
        'LEVELUPinformation_{team_name}.txt' inside the 'saved_information' directory.
        Otherwise, the information is saved in a file named 'information_{team_name}.txt'
        inside the 'saved_information' directory.

        The information includes the team name, attempt number, number of games played,
        inventory, and level.

        Returns:
            None
        """
        if self.level == 2:
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

    def train(self, conn):
        """
        Trains the collector agent by interacting with the environment.

        Args:
            conn: The connection object used to communicate with the environment.

        Returns:
            None
        """
        start_clock = time.time()
        while True:
            res = conn.send_request("Look")
            if res in ("done", None):
                self.train_long_memory()
                self.model.save()
                self.save_information()
                return
            res = res.decode()
            state_old = self.get_state(res)
            final_move = self.get_action(state_old)
            result = conn.send_request(self.command[final_move])
            self.add_item(result, self.command[final_move])
            elapsed_time = time.time() - start_clock
            reward = self.compute_reward(conn, self.command[final_move], result, elapsed_time)
            res = conn.send_request("Look")
            if res in ("done", None):
                self.train_long_memory()
                self.model.save()
                self.save_information()
                return
            res = res.decode()
            state_new = self.get_state(res)
            self.train_short_memory(state_old, final_move, reward, state_new, result)
            self.remember(state_old, final_move, reward, state_new, result)
