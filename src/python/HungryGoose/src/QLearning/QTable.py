import numpy as np

class QTable:
    def __init__(self, action_space):
        self.table = dict()
        self.action_space = action_space

    def add_item(self, state_key):
        self.table[state_key] = list(np.zeros(self.action_space.n))

    def __call__(self, state):
        board = state['board']  # Get a copy
        board = np.append(board, [1])
        state_key = np.array(board).astype(str)
        state_key = hex(int(''.join(state_key), 7))[2:]
        if state_key not in self.table.keys():
            self.add_item(state_key)

        return self.table[state_key]