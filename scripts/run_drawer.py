

import agent
import drawer
import animator
import model
import path
import stpoint

import matplotlib.pyplot as plt
import json
import sys


def print_usage():
    print "Usage:\n\tpython scripts/run_drawer.py [search json file name]"


def run():
    try:
        search_file = sys.argv[1]
        with open(search_file) as f:
            result = json.loads(f.read())
            agents = list()
            for ag in result["agents"]:
                model_x = model.models[ag["x"]["type"]](*ag["x"]["params"])
                model_y = model.models[ag["y"]["type"]](*ag["y"]["params"])
                agents.append(agent.Agent(model_x, model_y))

            b_path = path.make(list())
            for st_p in result["path"]:
                b_path.append(stpoint.make(st_p["x"], st_p["y"], st_p["t"]))

            fig = plt.figure()
            ax_dr = fig.add_subplot(111, projection="3d")

            dr = drawer.Drawer(fig, ax_dr)
            dr.draw_path(b_path)

            for ag in agents:
                dr.draw_agent(ag, b_path.get_max_time())

            dr.show()
    except IndexError:
        print_usage()


if __name__ == "__main__":
    run()
