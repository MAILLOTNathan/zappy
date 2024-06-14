from model import Linear_QNet, QTrainer
from collections import deque
import numpy as np
import random
import torch
import time
import os

MAX_MEMORY = 100_000
BATCH_SIZE = 1000   
LR = 0.5

def generate_sring():
    """
    Generate a random string and append it to the 'broadcast' variable.

    Returns:
        None
    """
    broadcast = "broadcast "
    string = "abcdefghijklmnopqrstuvwxyz"
    for i in range(10):
        broadcast += random.choice(string)

class TuringAI:
    def __init__(self):
        self.broadcast_string = generate_sring()
        self.debug = False
        self.port = None
        self.conn = None
        self.team_name = ""
        self.host = "localhost"
        self.command  = ['Forward', 'Left', 'Right', 'Take food', 'Take linemate', 'Take deraumere', 'Take sibur', 'Take mendiane', 'Take phiras', 'Take thystame', 
                  'Set food', 'Set linemate', 'Set deraumere', 'Set sibur', 'Set mendiane', 'Set phiras', 'Set thystame',
                  'Incantation', 'Fork', 'Eject', 'Broadcast', 'Connect_nbr']
        self.ngames = 0
        self.epsilon = 0
        self.gamma = 0.9
        self.memory = deque(maxlen=MAX_MEMORY)
        self.team_number = 0
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        
        self.model = Linear_QNet(618, 1233, 22).to(self.device)
        self.trainer = QTrainer(self.model, lr=LR, gamma=self.gamma)
        self.level = 1
        self.attempt = 0
        self.action = 0

        self.inventory = {"food": 10, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.level_requirements = {
            1: {"player": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
            2: {"player": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
            3: {"player": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
            4: {"player": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
            5: {"player": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
            6: {"player": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
            7: {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
        }

        self.children = 0

        try:
            self.model.load()
        except:
            print("Model not loaded")

    def update_inventory(self, response):
        """
        Update the agent's inventory based on the response received.

        Args:
            response (str): The response string containing the updated inventory information.

        Returns:
            None
        """
        if response == 'done':
            return
        if response is None:
            return

        response = response.decode()
        cleaned_response = response.replace("b'", "").replace("[", "").replace("]", "").replace("\n", "").replace("'", "")
        response_arr = cleaned_response.split(',')

        for item in response_arr:
            item = item.strip()
            if item == 'dead':
                continue
            try:
                item_name, item_quantity = item.split()
                self.inventory[item_name] = int(item_quantity)
            except ValueError:
                print(f"Skipping invalid inventory item: {item}")


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
        Get the state of the agent based on the response received.

        Args:
            response (str): The response received from the agent.

        Returns:
            numpy.ndarray: The state of the agent as a numpy array.

        """
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
        """
        Checks if the agent can level up based on the items in box_zero.

        Args:
            box_zero (list): The list of items in the agent's possession.

        Returns:
            bool: True if the agent can level up, False otherwise.
        """
        requirements = self.level_requirements[self.level]
        for item in requirements:
            if box_zero.count(item) < requirements[item]:
                return False
        return True
        
    def remember(self, state, action, reward, next_state, done):
        """
        Store the experience tuple (state, action, reward, next_state, done) in the agent's memory.

        Parameters:
        - state: The current state of the environment.
        - action: The action taken by the agent.
        - reward: The reward received after taking the action.
        - next_state: The resulting state after taking the action.
        - done: A flag indicating whether the episode is done or not.
        """
        self.memory.append((state, action, reward, next_state, done))

    def train_long_memory(self):
            """
            Trains the agent's long-term memory by sampling experiences from the memory buffer and performing a training step.

            If the memory buffer contains more experiences than the batch size, a random sample of size BATCH_SIZE is taken.
            Otherwise, the entire memory buffer is used as the sample.

            The sampled experiences are then unpacked into separate lists for states, actions, rewards, next states, and dones.
            These lists are passed to the trainer's `train_step` method for training.

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
        Returns the action to be taken based on the given state.

        Parameters:
        state (list): The current state of the agent.

        Returns:
        int: The index of the action to be taken.
        """
        self.epsilon = 300 - self.ngames
        final_move = len(self.command) * [0]
        if random.randint(0, 500) < self.epsilon:
            move = random.randint(0, len(self.command) - 1)
            final_move[move] = 1
        else:
            state0 = torch.tensor(state, dtype=torch.float).to(self.device)
            prediction = self.model(state0)
            move = torch.argmax(prediction).item()
            final_move[move] = 1
        return move

    def compute_reward(self, conn, final_move, result, elapsed_time, res):
        # if final_move is None:
        #     return 0
        # result_str = result.decode("utf-8") if isinstance(result, bytes) else result
        # first_part = result_str.split('[')[0]
        # if self.check_level_up(first_part):
        #     conn.s.recv(1024)
        #     self.level += 1
        #     return 100 * self.level
        # return 0

        """
        Computes the reward based on the final move, result, and elapsed time.

        Args:
            conn (connection): The connection object used for communication.
            final_move (str): The final move made by the agent.
            result (str or bytes): The result of the final move.
            elapsed_time (float): The elapsed time for the final move.

        Returns:
            int: The computed reward based on the final move and result.
        """
        result_str = result.decode("utf-8") if isinstance(result, bytes) else result
        if result_str is None:
            return -500
        if final_move is None:
            return -500
        elif "dead"in result_str:
            return -500
        elif self.check_level_up(res.split('[')[0]) == True and "Incantation" not in final_move:
            return -50
        elif "Incantation" in final_move and self.check_level_up(res.split('[')[0]) == True:
            return 1000 * self.level
        elif "Incantation" in final_move and self.check_level_up(res.split('[')[0]) == False:
            return -50
        else:
            return -elapsed_time

    def add_item(self, response, command):
        """
        Adds or removes an item from the agent's inventory based on the response and command.

        Args:
            response (str): The response received from the server.
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
            Saves the agent's information to a file.

            If the agent's level is greater than or equal to 2, the information is saved in a file named
            'LEVELUPinformation_{team_name}.txt' inside the 'saved_information' directory. Otherwise, the
            information is saved in a file named 'information_{team_name}.txt' inside the 'saved_information'
            directory.

            The saved information includes the team name, attempt number, number of games played, inventory,
            and level.

            Returns:
                None
            """
            if self.level >= 2:
                os.system("echo " + str(self.attempt) + " >> attempt.txt")
                os.makedirs("saved_information", exist_ok=True)
                with open(f"saved_information/LEVELUPinformation_{self.team_name}.txt", "w") as file:
                    file.write(f"Team name: {self.team_name}\n")
                    file.write(f"Attempt: {self.attempt}\n")
                    file.write(f"Games played: {self.ngames}\n")
                    file.write(f"Inventory: {self.inventory}\n")
                    file.write(f"Level: {self.level}\n")
                    file.write(f"action: {self.action}\n")
                return
            file_name = f"information_{self.team_name}.txt"
            os.makedirs("saved_information", exist_ok=True)
            with open(f"saved_information/{file_name}", "w") as file:
                file.write(f"Team name: {self.team_name}\n")
                file.write(f"Attempt: {self.attempt}\n")
                file.write(f"Games played: {self.ngames}\n")
                file.write(f"Inventory: {self.inventory}\n")
                file.write(f"Level: {self.level}\n")
                file.write(f"action: {self.action}\n")

    def launch_new_instance(self):
        """
        Launches a new instance based on the current state of the agent.

        If the agent's food inventory is less than 10, it launches the `sucide.py` script.
        If the agent's level is 2 and the food inventory is greater than or equal to 10, it launches the `evolver.py` script.
        Otherwise, it launches the `collector.py` script.

        The launched scripts are executed in the background and their output is redirected to separate log files.

        Returns:
            None
        """
        if self.inventory["food"] < 10:
            os.system("python sucide.py -p " + str(self.port) + " -n " + self.team_name + " -h " + self.host + "&")
            self.children += 1
            return
        elif self.level > 2 and self.inventory["food"] >= 10:
            os.system("python evolver.py -p " + str(self.port) + " -n " + self.team_name + " -h " + self.host + "&")
            self.children += 1
            return
        else:
            os.system("python collector.py -p " + str(self.port) + " -n " + self.team_name + " -h " + self.host + "&")
            self.children += 1
            return


    def can_fork(self, action, result):
        """
        Checks if forking is possible based on the action and result.

        Args:
            action (str): The action being performed.
            result (str or bytes): The result of the action.

        Returns:
            bool: True if forking is possible, False otherwise.
        """
        if self.conn.conn_num == self.children:
            return False
        if result is None:
            return False
        result_str = result.decode("utf-8") if isinstance(result, bytes) else result
        if "Fork" in action and "ok" in result_str:
            return True
        return False

    def train(self, conn):
        """
        Trains the agent using the given connection.

        Args:
            conn: The connection object used to communicate with the environment.

        Returns:
            None
        """
        while True:
            inv = conn.send_request("Inventory")
            self.update_inventory(inv)
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
            start_clock = time.time()
            if self.command[final_move] == "Incantation":
                result = conn.send_request(self.command[final_move])
                self.action += 1
                if result != "ko":
                    conn.s.recv(1024)
            result = conn.send_request(self.command[final_move])
            self.action +=1
            if self.can_fork(self.command[final_move], result):
                self.launch_new_instance()
            self.add_item(result, self.command[final_move])
            elapsed_time = time.time() - start_clock
            reward = self.compute_reward(conn, self.command[final_move], result, elapsed_time, res)
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
