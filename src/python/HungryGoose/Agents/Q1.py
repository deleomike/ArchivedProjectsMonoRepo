def my_agent(observation, configuration):
            from random import choice
            import numpy as np
            from kaggle_environments.envs.hungry_geese.hungry_geese import Observation, Configuration, Action, row_col


            observation = Observation(observation)
            configuration = Configuration(configuration)
            actions = ['NORTH', 'EAST', 'SOUTH', 'WEST']

            board = np.array(np.zeros(77), dtype=int)
            board[observation.food] = 5

            for indx, goose in enumerate(observation.geese):
                board[goose] = indx

            np.append(board, [1])
            state_key = list(map(str, board))
            state_key = hex(int(''.join(state_key), 6))[2:]


            if state_key not in q_table.keys():
                # return "EAST"
                return actions[choice([c for c in range(4) if board[c] == 0])]


            action = q_table[state_key]

            if board[action] != 0:
                return actions[choice([c for c in range(4) if observation.board[c] == 0])]

            return action
            