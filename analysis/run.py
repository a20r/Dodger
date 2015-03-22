
import table
import matplotlib.pyplot as plt
import seaborn as sns


def plot_data(tb, speed, means, stds):
    xs = tb("speed", value=speed, s_index="noise")
    ys = tb("speed", value=speed, s_index=means)
    ss = tb("speed", value=speed, s_index=stds)
    plt.errorbar(xs, ys, fmt='x-', yerr=ss, label="Speed = {}".format(speed))


if __name__ == "__main__":
    tb = table.load_csv("data/planner_speed_noise_0.csv")
    plt.figure()
    plot_data(tb, 1, "mean_min_distance", "std_min_distance")
    plot_data(tb, 1.5, "mean_min_distance", "std_min_distance")
    plot_data(tb, 2, "mean_min_distance", "std_min_distance")
    plot_data(tb, 2.5, "mean_min_distance", "std_min_distance")
    plt.legend()

    plt.figure()
    plot_data(tb, 1, "mean_avg_min_distance", "std_avg_min_distance")
    plot_data(tb, 1.5, "mean_avg_min_distance", "std_avg_min_distance")
    plot_data(tb, 2, "mean_avg_min_distance", "std_avg_min_distance")
    plot_data(tb, 2.5, "mean_avg_min_distance", "std_avg_min_distance")
    plt.legend()

    plt.show()
