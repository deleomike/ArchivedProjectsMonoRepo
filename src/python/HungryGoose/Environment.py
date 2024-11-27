import numpy as np
import gym
import random
from kaggle_environments import evaluate, make

from Agents.Q1 import my_agent
from Agents.Greedy import agent as Greedy

class HungryGoose(gym.Env):

    def __init__(self, width=450, switch_prob=0.5):
        self.env = make('hungry_geese', debug=False)
        self.pair = [None, Greedy]
        self.trainer = self.env.train(self.pair)
        self.switch_prob = switch_prob

        # Define required gym fields (examples):
        config = self.env.configuration
        self.actions = ['NORTH', 'EAST', 'SOUTH', 'WEST']
        self.offsets = [-config.columns, 1, config.columns, -1]
        self.action_space = gym.spaces.Discrete(len(self.actions))
        self.observation_space = gym.spaces.Discrete(config.columns * config.rows)


    def switch_trainer(self):
        self.pair = self.pair[::-1]
        self.trainer = self.env.train(self.pair)



    def step(self, action):
        next_state, reward, done, info = self.trainer.step(action)
        # np.zeros(0).
        next_state['board'] = np.array(np.zeros(self.observation_space.n), dtype=int)
        next_state['board'][next_state['food']] = 6

        for indx, goose in enumerate(next_state['geese']):
            next_state['board'][goose] = indx + 1
        return next_state, reward, done, info



    def reset(self):
        if random.uniform(0, 1) < self.switch_prob:
            self.switch_trainer()
        res = self.trainer.reset()

        # np.zeros(0).
        res['board'] = np.array(np.zeros(self.observation_space.n), dtype=int)
        res['board'][res['food']] = 6

        for indx, goose in enumerate(res['geese']):
            res['board'][goose] = indx + 1


        return res


    def render(self, **kwargs):
        return self.env.render(**kwargs)

if __name__=="__main__":

    hg = HungryGoose()