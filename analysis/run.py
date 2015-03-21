
import table


def main():
    tb = table.load_csv("data/planner_speed_noise_0.csv")
    print tb("speed", value=1, s_index="mean_min_distance")


if __name__ == "__main__":
    main()
