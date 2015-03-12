

import agent
import animator
import model
import path
import stpoint

import matplotlib.pyplot as plt
import json
import sys


def print_usage():
    print "Usage:\n\tpython scripts/run_animator.py [search json file name] "\
        + "[figure output directory]"


def run():
    try:
        search_file = sys.argv[1]
        with open(search_file) as f:
            result = json.loads(f.read())
            agents = list()
            for ag in result["agents"]:
                try:
                    model_x = model.models[ag["x"]["type"]](*ag["x"]["params"])
                    model_y = model.models[ag["y"]["type"]](*ag["y"]["params"])
                    agents.append(agent.Agent(model_x, model_y))
                except TypeError:
                    agents.append(path.make(list()))
                    for p in ag:
                        agents[-1].append(stpoint.make(p["x"], p["y"], p["t"]))

            b_path = path.make(list())
            for st_p in result["path"]:
                b_path.append(stpoint.make(st_p["x"], st_p["y"], st_p["t"]))

            fig = plt.figure()
            ax_an = fig.add_subplot(111)

            anmtr = animator.Animator(fig, ax_an, b_path, *agents,
                                      fig_dir=sys.argv[2])
            anmtr.run()
    except IndexError:
        print_usage()


if __name__ == "__main__":
    run()
