from kaggle_environments import evaluate, make, utils

import webbrowser
import submission

from Agents.Q1 import my_agent as Q1
from Agents.Greedy import agent as Greedy

class Evaluator:

    def __init__(self, debug=True, width=500, height=450):

        self.game = "hungry_geese"
        # Setup a hungry_geese environment.
        self.env = make(self.game, debug=debug)
        self.width = width
        self.height = height

    def show(self, protagonist, antagonist="random"):

        print(self.env.render(mode="ansi"))
        self.env.run([protagonist, antagonist, antagonist, antagonist])
        html = self.env.render(mode="html")
        f = open("output.html", "w")

        f.write(html)

        f.close()

        path = "file://Users/michaeldeleo/PycharmProjects/HungryGoose/output.html"

        webbrowser.open_new_tab(path)

    def evaluate(self, protagonist, antagonist="random", num_episodes=10):

        def mean_reward(rewards):
            return sum(r[0] for r in rewards) / float(len(rewards))

        print("Score (Mean)", mean_reward(evaluate(self.game, [protagonist, antagonist, antagonist, antagonist], num_episodes=num_episodes)))


if __name__ == "__main__":

    eval = Evaluator()

    eval.evaluate(protagonist=submission.my_agent, antagonist=Greedy)

    eval.show(submission.my_agent, antagonist=Greedy)