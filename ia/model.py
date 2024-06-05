import torch
import torch.nn as nn
import torch.optim as optim
import os

class Linear_QNet(nn.Module):
    """
    A linear Q-network model.

    Args:
        input_size (int): The size of the input.
        hidden_size (int): The size of the hidden layer.
        output_size (int): The size of the output.

    Attributes:
        linear1 (nn.Linear): The first linear layer.
        linear2 (nn.Linear): The second linear layer.

    Methods:
        forward(x): Performs forward pass through the network.
        save(file_name='model.pth'): Saves the model's state dictionary to a file.
    """

    def __init__(self, input_size, hidden_size, output_size):
        """
        Initializes a new instance of the Model class.

        Args:
            input_size (int): The size of the input layer.
            hidden_size (int): The size of the hidden layer.
            output_size (int): The size of the output layer.
        """
        super().__init__()
        self.linear1 = nn.Linear(input_size, hidden_size)
        self.linear2 = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        """
        Forward pass of the model.

        Args:
            x (torch.Tensor): Input tensor.

        Returns:
            torch.Tensor: Output tensor.
        """
        x = torch.relu(self.linear1(x))
        x = self.linear2(x)
        return x
    
    def save(self, file_name='model.pth'):
        """
        Saves the model's state dictionary to a file.

        Args:
            file_name (str): The name of the file to save the model to. Defaults to 'model.pth'.
        """
        model_folder_path = './model'
        if not os.path.exists(model_folder_path):
            os.makedirs(model_folder_path)
        file_name = os.path.join(model_folder_path, file_name)
        torch.save(self.state_dict(), file_name)

class QTrainer:
    """
    QTrainer class for training a Q-learning model.

    Args:
        model (torch.nn.Module): The Q-learning model.
        lr (float): The learning rate for the optimizer.
        gamma (float): The discount factor for future rewards.

    Attributes:
        lr (float): The learning rate for the optimizer.
        gamma (float): The discount factor for future rewards.
        model (torch.nn.Module): The Q-learning model.
        optimizer (torch.optim.Optimizer): The optimizer for updating the model's parameters.
        criterion (torch.nn.Module): The loss function for calculating the training loss.

    Methods:
        train_step: Performs a single training step.

    """

    def __init__(self, model, lr, gamma):
        """
        Initialize the Model class.

        Args:
            model (torch.nn.Module): The neural network model.
            lr (float): The learning rate for the optimizer.
            gamma (float): The discount factor for the loss function.

        Attributes:
            lr (float): The learning rate for the optimizer.
            gamma (float): The discount factor for the loss function.
            model (torch.nn.Module): The neural network model.
            optimizer (torch.optim.Adam): The optimizer for updating the model parameters.
            criterion (torch.nn.MSELoss): The loss function for calculating the mean squared error.

        """
        self.lr = lr
        self.gamma = gamma
        self.model = model
        self.optimizer = optim.Adam(model.parameters(), lr=self.lr)
        self.criterion = nn.MSELoss()

    def train_step(self, state, action, reward, next_state, done):
        """
        Performs a single training step.

        Args:
            state (list or numpy.ndarray): The current state.
            action (int): The action taken in the current state.
            reward (float): The reward received for taking the action.
            next_state (list or numpy.ndarray): The next state after taking the action.
            done (bool): Whether the episode is done after taking the action.

        """
        state = torch.tensor(state, dtype=torch.float)
        next_state = torch.tensor(next_state, dtype=torch.float)
        action = torch.tensor(action, dtype=torch.long)
        reward = torch.tensor(reward, dtype=torch.float)

        if (len(state.shape) == 1):
            state = torch.unsqueeze(state, 0)
            next_state = torch.unsqueeze(next_state, 0)
            action = torch.unsqueeze(action, 0)
            reward = torch.unsqueeze(reward, 0)
            done = (done, )

        pred = self.model(state)

        target = pred.clone()
        for idx in range(len(done)):
            Q_new = reward[idx]
            if not done[idx]:
                Q_new = reward[idx] + self.gamma * torch.max(self.model(next_state[idx]))
            if torch.argmax(action).item() >= 20:
                return
            target[idx][torch.argmax(action).item()] = Q_new

        self.optimizer.zero_grad()
        loss = self.criterion(target, pred)
        loss.backward()

        self.optimizer.step()