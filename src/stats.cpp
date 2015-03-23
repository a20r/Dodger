
#include <iostream>
#include <cmath>
#include "stats.hpp"

namespace Dodger {
    double Stats::avg_min_distance(Path path, list<Agent *> ags) {
        double dt = 0.05;
        double tc = path.get(0).get_t();
        double max_time = path.get_list().back().get_t();
        double min_dist_sum = 0.0;
        int num_dists = 0;
        while (tc <= max_time) {
            Point p_pos = path.get_position(tc);
            double min_dist = -1;
            for (Agent *ag : ags) {
                Point ag_pos = Path(ag->get_path()).get_position(tc);
                double dist = ag_pos.euclid_dist(p_pos);
                if (min_dist < 0 || dist < min_dist) {
                    min_dist = dist;
                }
            }

            num_dists++;
            min_dist_sum += min_dist;
            tc += dt;
        }
        return min_dist_sum / num_dists;
    }

    double Stats::min_distance(Path path, list<Agent *> ags) {
        double dt = 0.05;
        double tc = path.get(0).get_t();
        double max_time = path.get_list().back().get_t();
        double min_dist = -1;
        while (tc <= max_time) {
            Point p_pos = path.get_position(tc);
            for (Agent *ag : ags) {
                Point ag_pos = Path(ag->get_path()).get_position(tc);
                double dist = ag_pos.euclid_dist(p_pos);
                if (min_dist < 0 || dist < min_dist) {
                    min_dist = dist;
                }
            }

            tc += dt;
        }
        return min_dist;
    }

    double Stats::mean(double arr[], int size) {
        double sum = 0.0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
        }

        return sum / size;
    }

    double Stats::std(double arr[], int size) {
        double mu = mean(arr, size);
        double sum = 0.0;

        for (int i = 0; i < size; i++) {
            sum += pow(arr[i] - mu, 2);
        }

        return sqrt(sum / size);
    }

    pair<double, double> Stats::costs(Path path, list<Agent *> ags) {
        double dt = 0.05;
        double max_cost = -1;
        int counter = 0;
        double cost_sum = 0.0;

        for (int i = 0; i < path.get_list().size() - 1; i++) {
            double tc = path.get(i).get_t();
            double max_time = path.get(i + 1).get_t();
            while (tc <= max_time) {
                counter++;
                Point p_pos = path.get_position(tc);
                double cost = Agent::get_probability(p_pos.get_x(),
                        p_pos.get_y(), tc, max_time, ags);
                if (max_cost < 0 || cost > max_cost) {
                    max_cost = cost;
                }
                cost_sum += cost;
                tc += dt;
            }
        }

        return make_pair(max_cost, cost_sum / counter);
    }
}
