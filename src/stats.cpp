
#include <iostream>
#include "stats.hpp"

namespace Dodger {
    double Stats::avg_min_distance(Path path, list<Agent *> ags) {
        double dt = 0.1;
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
        double dt = 0.1;
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
}
