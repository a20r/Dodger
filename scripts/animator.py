
import matplotlib.pyplot as plt
import warnings


class Animator(object):

    def __init__(self, fig, ax, path, *agents, **kwargs):
        warnings.filterwarnings("ignore")
        plt.ion()
        self.fig = fig
        self.ax = ax
        self.ax.set_xlabel("X Location")
        self.ax.set_ylabel("Y Location")
        self.ax.set_xlim(kwargs.get("x_min", -1), kwargs.get("x_max", 5))
        self.ax.set_ylim(kwargs.get("y_min", -1), kwargs.get("y_max", 5))
        self.path = path
        self.agents = agents
        self.agent_plots = [self.ax.scatter([], []) for _ in agents]
        self.pln_plot = self.ax.scatter([], [])
        self.goal_x = path[-1].x
        self.goal_y = path[-1].y

    def update(self, t):
        pln_pos = self.path(t)
        self.pln_plot.remove()
        self.pln_plot = self.ax.scatter(
            [pln_pos.x], [pln_pos.y], marker="o", color="b", s=40)

        for i, ag in enumerate(self.agents):
            ag_pos = ag.get_position(t)
            self.agent_plots[i].remove()
            self.agent_plots[i] = self.ax.scatter(
                [ag_pos.x], [ag_pos.y], marker="^", color="r", s=40)

        plt.draw()
        plt.pause(0.00001)

    def run(self):
        time_step = 0.05
        t = 0
        i = 0
        self.ax.scatter(
            [self.goal_x], [self.goal_y], marker="o", color="g", s=200)
        while t < self.path[-1].t:
            self.update(t)
            plt.savefig("sandbox/figs/%05d.png" % i)
            i += 1
            t += time_step
