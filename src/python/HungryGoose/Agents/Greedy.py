from kaggle_environments.envs.hungry_geese.hungry_geese import Observation, Configuration, Action, row_col
import random


def agent(obs_dict, config_dict):
    global previous_direction
    observation = Observation(obs_dict)
    configuration = Configuration(config_dict)
    player_index = observation.index
    player_goose = observation.geese[player_index]
    player_head = player_goose[0]
    player_row, player_column = row_col(player_head, configuration.columns)
    if observation.step == 0:
        previous_direction = None
    # print("Player pos", player_row, player_column)
    foods = observation.food
    distances = []
    for i in range(len(foods)):
        food_row, food_column = row_col(foods[i], configuration.columns)
        total_distance = (food_row - player_row) ** 2 + (food_column - player_column) ** 2
        distances.append(total_distance)
    min_distance_index = distances.index(min(distances))
    closest_food = foods[min_distance_index]
    food_row, food_column = row_col(foods[min_distance_index], configuration.columns)
    # print("Goose at", player_row, player_column)

    directions = {"NORTH": [-1, 0], "SOUTH": [1, 0], "EAST": [0, 1], "WEST": [0, -1]}
    directions_2 = {"NORTH": Action.NORTH.name, "SOUTH": Action.SOUTH.name, "EAST": Action.EAST.name,
                    "WEST": Action.WEST.name}
    allowed_directions = list(directions_2.values())
    # print("Allowed directions", allowed_directions)
    forbidden_directions = []

    banned_directions = {"EAST": "WEST", "WEST": "EAST", "NORTH": "SOUTH", "SOUTH": "NORTH"}
    if previous_direction is not None:
        banned_direction = banned_directions[previous_direction]
    else:
        banned_direction = None
    row_difference = abs(food_row - player_row)
    col_difference = abs(food_column - player_column)

    other_row_difference = 7 - row_difference
    other_col_difference = 11 - col_difference

    if banned_direction is not None:
        allowed_directions.remove(banned_direction)
        forbidden_directions.append(banned_direction)
    print(forbidden_directions)

    # print("Food row, player row", food_row, player_row)
    # print("Food col, player col", food_column, player_column)
    direction = None
    if food_row > player_row:
        if row_difference > other_row_difference and "NORTH" not in forbidden_directions:
            direction = "NORTH"
        elif row_difference < other_row_difference and "SOUTH" not in forbidden_directions:
            direction = "SOUTH"
    if food_row < player_row:
        if row_difference < other_row_difference and "NORTH" not in forbidden_directions:
            direction = "NORTH"
        elif row_difference > other_row_difference and "SOUTH" not in forbidden_directions:
            direction = "SOUTH"

    if food_column > player_column:
        if col_difference < other_col_difference and "EAST" not in forbidden_directions:
            direction = "EAST"
        elif col_difference > other_col_difference and "WEST" not in forbidden_directions:
            direction = "WEST"
    if food_column < player_column:
        if col_difference > other_col_difference and "EAST" not in forbidden_directions:
            direction = "EAST"
        elif col_difference < other_col_difference and "WEST" not in forbidden_directions:
            direction = "WEST"

    if direction is None:
        print("Moving in random direction")
        return random.choice(allowed_directions)

    add_row = directions[direction][0]
    add_col = directions[direction][1]
    new_row = player_row + add_row
    new_column = player_column + add_col

    number_of_geese = len(observation.geese)
    for i in range(number_of_geese):
        opposing_geese = observation.geese[i]
        for val in opposing_geese:
            row, col = row_col(val, configuration.columns)
            if row == new_row and col == new_column:
                if directions_2[direction] not in forbidden_directions:
                    forbidden_directions.append(directions_2[direction])
                if directions_2[direction] in allowed_directions:
                    allowed_directions.remove(directions_2[direction])

    previous_direction = directions_2[direction]
    if directions_2[direction] not in forbidden_directions:
        return directions_2[direction]