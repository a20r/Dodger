
#include <iostream>
#include <vector>
#include <tr1/unordered_map>
#include "planner.hpp"

namespace Dodger {

    Planner::Planner(Search search, list<Agent *> agents,
            double goal_radius, double pred_dev) {
        this->search = search;
        this->agents = agents;
        this->goal_radius = goal_radius;
        this->pred_dev = pred_dev;
    }

    Path Planner::get_path(Point start, Point goal) {
        vector<STPoint> stp_list;
        stp_list.push_back(STPoint(start.get_x(), start.get_y(), 0));
        Point current_pt = start;
        STPoint next_st;
        double current_time = 0, diff;
        bool replan = false;
        std::tr1::unordered_map<std::string, int> num_visited;
        while (stp_list.back().euclid_dist(goal) > this->goal_radius) {

            Path path = this->search.get_path(current_pt, goal, agents,
                        num_visited, current_time);

            for (int i = 0; i < path.get_list().size(); i++) {
                STPoint stp = path.get(i);
                stp_list.push_back(stp);
                replan = false;
                for (Agent *ag : this->agents) {
                    ag->step(stp.get_t());
                    diff = ag->get_difference(stp.get_t());
                    if (diff > this->pred_dev) {
                        replan = true;
                    }
                }

                if (replan) {
                    for (Agent *ag : this->agents) {
                        ag->update_starting_positions();
                    }

                    current_pt = Point(stp.get_x(), stp.get_y());
                    current_time = stp.get_t();
                    break;
                }
            }
        }

        return Path(stp_list);
    }
}
