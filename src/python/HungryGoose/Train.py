import matplotlib.pyplot as plt
import numpy as np

import random

from random import choice
from tqdm import tqdm

from Environment import HungryGoose
from src.QLearning.QTable import QTable

class QTrainer:

    def __init__(self):

        # Create Env
        self.env = HungryGoose()

        # hyperparameters
        self.alpha = 0.3
        self.gamma = 0.6
        self.epsilon = 0.99
        self.min_epsilon = 0.1

        self.reset_qtable()

    def reset_qtable(self):
        print("Q Table init")
        self.q_table = QTable(self.env.action_space)

    def save_agent(self):

        tmp_q_table = self.q_table.table.copy()
        dict_q_table = dict()

        for k in tmp_q_table:
            if np.count_nonzero(tmp_q_table[k]) > 0:
                dict_q_table[k] = int(np.argmax(tmp_q_table[k]))

        my_agent = '''def my_agent(observation, configuration):
            from random import choice
            import numpy as np
            from kaggle_environments.envs.hungry_geese.hungry_geese import Observation, Configuration, Action, row_col

            q_table = ''' \
                   + str(dict_q_table).replace(' ', '') \
                   + '''

            observation = Observation(observation)
            configuration = Configuration(configuration)
            actions = ['NORTH', 'EAST', 'SOUTH', 'WEST']

            board = np.array(np.zeros(77), dtype=int)
            board[observation.food] = 6

            for indx, goose in enumerate(observation.geese):
                board[goose] = indx + 1

            np.append(board, [1])
            state_key = list(map(str, board))
            state_key = hex(int(''.join(state_key), 7))[2:]


            if state_key not in q_table.keys():
                # return "EAST"
                return actions[choice([c for c in range(4) if board[c] == 0])]


            action = q_table[state_key]

            if board[action] != 0:
                return actions[choice([c for c in range(4) if observation.board[c] == 0])]

            return action
            '''

        print("Writing Agent")
        with open('submission.py', 'w') as f:
            f.write(my_agent)


    def train(self, episodes=10000):


        alpha_decay_step = 1000
        alpha_decay_rate = 0.9
        epsilon_decay_rate = 0.9999


        all_epochs = []
        all_total_rewards = []
        all_avg_rewards = []  # Last 100 steps
        all_qtable_rows = []
        all_epsilons = []

        for i in tqdm(range(episodes)):
            state = self.env.reset()

            epsilon = max(self.min_epsilon, self.epsilon * epsilon_decay_rate)
            epochs, total_rewards = 0, 0
            done = False

            while not done:

                head = state['geese'][0][0]

                if random.uniform(0, 1) < epsilon:
                    #TODO: Proper actions...
                    action = 0
                    locations = []
                    food_locations = []
                    for c in range(self.env.action_space.n):
                        loc = head - self.env.offsets[c]

                        if loc < 0:
                            loc = 77 + loc

                        if loc >= 77:
                            loc = loc - 77

                        if state['board'][loc] == 0:
                            locations.append(c)

                        if state['board'][loc] == 6:
                            food_locations.append(c)

                    if len(food_locations) > 0:
                        action = choice(food_locations)
                    else:
                        action = choice(locations)

                else:
                    action = np.argmax(self.q_table(state))

                action_cmd = self.env.actions[action]

                ansi_board = self.env.render(mode="ansi")

                next_state, reward, done, info = self.env.step(action_cmd)
                try:
                    next_head = next_state['geese'][0][0]
                except:
                    # reward = reward - 20 # lost
                    done = True

                # Apply new rules
                if done:
                    reward = reward + 2 * len(state['geese'][0]) + state['index']
                    # if reward == 1:  # Won
                    #     reward = 20
                    # elif reward == 0:  # Lost
                    #     reward = -20
                else:
                    reward = reward + len(state['geese'][0]) + state['index'] # Try to prevent the agent from taking a long move


                old_value = self.q_table(state)[action]
                next_max = np.max(self.q_table(next_state))

                # Update Q-value
                new_value = (1 - self.alpha) * old_value + self.alpha * (reward + self.gamma * next_max)
                self.q_table(state)[action] = new_value

                state = next_state
                epochs += 1
                total_rewards += reward

            all_epochs.append(epochs)
            all_total_rewards.append(total_rewards)
            avg_rewards = np.mean(all_total_rewards[max(0, i - 100):(i + 1)])
            all_avg_rewards.append(avg_rewards)
            # all_qtable_rows.append(len(q_table.table))
            all_epsilons.append(epsilon)

            if (i + 1) % alpha_decay_step == 0:
                self.alpha *= alpha_decay_rate

        # print(len(q_table.table))

        plt.plot(all_avg_rewards)
        plt.xlabel('Episode')
        plt.ylabel('Avg rewards ({})'.format(episodes))
        plt.show()

        plt.plot(all_qtable_rows)
        plt.xlabel('Episode')
        plt.ylabel('Explored states')
        plt.show()

        plt.plot(all_epsilons)
        plt.xlabel('Episode')
        plt.ylabel('Epsilon')
        plt.show()

if __name__=="__main__":

    qt = QTrainer()

    qt.train(episodes=10000)

    qt.save_agent()