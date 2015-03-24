
# fucking python
__all__ = ["sns"]

import table
import matplotlib.pyplot as plt
import seaborn as sns


name_dict = {"pf": "Potential Fields", "planner": "Dodger"}

metric_dict = {"mean_min_distance": "Mean Minimum Distance",
               "mean_avg_min_distance": "Mean Average Minimum Distance",
               "avg_times": "Average Computational Time"}


def plot_speed_data(tb, speed, means, stds, yunit):
    xs = tb("speed", value=speed, s_index="noise")
    ys = tb("speed", value=speed, s_index=means)
    ss = tb("speed", value=speed, s_index=stds)
    plt.xlabel("Meters [m]")
    plt.ylabel(yunit)
    plt.errorbar(xs, ys, fmt='x-', yerr=ss, label="Speed = {}".format(speed))


def plot_speed_vs(tb, means, stds, yunit):
    speeds = [1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5]
    for speed in speeds:
        plot_speed_data(tb, speed, means, stds, yunit)


def plot_speed_planner(planner, i):
    tb = table.load_csv("data/{}_speed_noise_{}.csv".format(planner, i))
    plt.figure()
    plot_speed_vs(tb, "mean_min_distance", "std_min_distance", "Meters [m]")
    plt.title("{}: Noise v.s. Mean Minimum Distance"
              .format(name_dict[planner]))
    plt.legend()

    plt.figure()
    plot_speed_vs(tb, "mean_avg_min_distance", "std_avg_min_distance",
                  "Meters [m]")
    plt.title("{}: Noise v.s. Mean Average Minimum Distance"
              .format(name_dict[planner]))
    plt.legend()

    plt.figure()
    plot_speed_vs(tb, "avg_times", "std_times", "Seconds [s]")
    plt.title("{}: Noise v.s. Mean Computational Time"
              .format(name_dict[planner]))
    plt.legend()


def plot_noise_data(tb, noise, means, stds, yunit):
    xs = tb("noise", value=noise, s_index="speed")
    ys = tb("noise", value=noise, s_index=means)
    ss = tb("noise", value=noise, s_index=stds)
    plt.xlabel("Speed [m/s]")
    plt.ylabel(yunit)
    plt.errorbar(xs, ys, fmt='x-', yerr=ss,
                 label="$\epsilon$ = {}".format(noise))


def plot_noise_vs(tb, means, stds, yunit):
    noises = [0.002, 0.004, 0.006, 0.008, 0.01]
    for noise in noises:
        plot_noise_data(tb, noise, means, stds, yunit)


def plot_noise_planner(planner, i):
    tb = table.load_csv("data/{}_speed_noise_{}.csv".format(planner, i))
    plt.figure()
    plot_noise_vs(tb, "mean_min_distance", "std_min_distance", "Mean Minimum Distance [m]")
    plt.title("{}: Speed v.s. Mean Minimum Distance"
              .format(name_dict[planner]))
    plt.ylim([0, 0.6])

    if planner == "planner":
        plt.legend(loc=2)
    else:
        plt.legend()

    plt.savefig("figures/{}_mean_min_distance_{}.pdf".format(planner, i),
                bbox_inches="tight")

    plt.figure()
    plot_noise_vs(tb, "mean_avg_min_distance", "std_avg_min_distance",
                  "Mean Average Minimum Distance [m]")
    plt.title("{}: Speed v.s. Mean Average Minimum Distance"
              .format(name_dict[planner]))
    plt.legend()
    plt.savefig("figures/{}_mean_avg_min_distance_{}.pdf".format(planner, i),
                bbox_inches="tight")

    plt.figure()
    plot_noise_vs(tb, "avg_times", "std_times", "Time [s]")
    plt.title("{}: Speed v.s. Mean Computational Time"
              .format(name_dict[planner]))
    plt.legend()
    plt.savefig("figures/{}_mean_times_{}.pdf".format(planner, i),
                bbox_inches="tight")

    plt.figure()
    plot_noise_vs(tb, "mean_max_cost", "std_max_cost", "Mean Maximum Cost")
    plt.title("{}: Speed v.s. Mean Maximum Planner Cost"
              .format(name_dict[planner]))
    plt.legend()
    plt.ylim([0, 0.5])
    plt.savefig("figures/{}_mean_max_cost_{}.pdf".format(planner, i),
                bbox_inches="tight")

    plt.figure()
    plot_noise_vs(tb, "mean_avg_cost", "std_avg_cost", "Mean Average Cost")
    plt.title("{}: Speed v.s. Mean Average Planner Cost"
              .format(name_dict[planner]))
    plt.legend()
    plt.ylim([0, 0.06])
    plt.savefig("figures/{}_mean_avg_cost_{}.pdf".format(planner, i),
                bbox_inches="tight")


def plot_noise_std_data(tb, speed, stds, yunit):
    xs = tb("speed", value=speed, s_index="noise")
    ys = tb("speed", value=speed, s_index=stds)
    plt.xlabel("Obstacle Position Uncertainty [m]")
    plt.ylabel(yunit)
    plt.plot(xs, ys, 'x-', label="Speed = {}".format(speed))


def plot_noise_std_vs(tb, stds, yunit):
    speeds = [1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5]
    for speed in speeds:
        plot_noise_std_data(tb, speed, stds, yunit)


def plot_noise_std_planner(planner, i):
    tb = table.load_csv("data/{}_speed_noise_{}.csv".format(planner, i))
    plt.figure()
    plot_noise_std_vs(tb, "std_min_distance", "Standard Deviation [m]")
    plt.title("{}: Noise v.s. Mean Minimum Distance Standard Deviation"
              .format(name_dict[planner]))
    plt.legend(loc=2)
    plt.savefig("figures/{}_std_min_distance_{}.pdf".format(planner, i),
                bbox_inches="tight")

    plt.figure()
    plot_noise_std_vs(tb, "std_avg_min_distance",
                  "Standard Deviation [m]")
    plt.title("{}: Noise v.s. Mean Average Distance Standard Deviation"
              .format(name_dict[planner]))
    plt.legend(loc=2)
    plt.savefig("figures/{}_std_avg_distance_{}.pdf".format(planner, i),
                bbox_inches="tight")

    plt.figure()
    plot_noise_std_vs(tb, "std_times", "Standard Deviation [s]")
    plt.title("{}: Noise v.s. Mean Computational Time Standard Deviation"
              .format(name_dict[planner]))
    plt.legend(loc=2)
    plt.savefig("figures/{}_std_avg_times_{}.pdf".format(planner, i),
                bbox_inches="tight")

    plt.figure()
    plot_noise_std_vs(tb, "std_max_cost", "Mean Maximum Cost")
    plt.title("{}: Noise v.s. Mean Maximum Cost Standard Deviation"
              .format(name_dict[planner]))
    plt.legend(loc=2)
    plt.savefig("figures/{}_std_max_cost_{}.pdf".format(planner, i),
                bbox_inches="tight")

    plt.figure()
    plot_noise_std_vs(tb, "std_avg_cost", "Mean Average Cost")
    plt.title("{}: Noise v.s. Mean Average Cost Standard Deviation"
              .format(name_dict[planner]))
    plt.legend(loc=2)
    plt.savefig("figures/{}_std_avg_cost_{}.pdf".format(planner, i),
                bbox_inches="tight")


if __name__ == "__main__":
    plot_noise_planner("planner", 0)
    plot_noise_planner("pf", 0)
    plot_noise_std_planner("planner", 0)
    plot_noise_std_planner("pf", 0)
    # plt.show()
