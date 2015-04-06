
#include <iostream>
#include <vector>
#include "pf.hpp"

namespace Dodger {

    PF::PF(list<Agent *> agents, double goal_radius, double speed,
            double dt, int num_samples) {
        this->agents = agents;
        this->goal_radius = goal_radius;
        this->speed = speed;
        this->dt = dt;
        this->num_samples = num_samples;
    }

    double PF::goal_potential(Point position, Point goal) {
        double dist = position.euclid_dist(goal);
        return dist * dist;
    }

    double PF::obstacle_potential(Point position, double t) {
        double pot_sum = 0, dist;

        for (Agent *ag : this->agents) {
            dist = ag->get_position(t).euclid_dist(position);
            if (dist < MIN_DIST) {
                dist = MIN_DIST;
            }

            pot_sum += 10 / (pow(dist - MIN_DIST, 2) + 0.1);
        }


        return pot_sum;
    }

    double PF::get_potential(Point position, Point goal, double t) {
        return this->goal_potential(position, goal)
            + obstacle_potential(position, t);
    }

    STPoint PF::get_best_sample(Point position, Point goal, double t) {
        double d_theta = 2 * M_PI / this->num_samples;
        double theta = 0;
        double x, y, current_pot;
        double best_potential = -1;
        STPoint best_point, current;
        while (theta < 2 * M_PI) {
            x = position.get_x() + cos(theta) * this->speed * this->dt;
            y = position.get_y() + sin(theta) * this->speed * this->dt;
            current = STPoint(x, y, t + dt);
            current_pot = this->get_potential(current, goal, t);
            if (best_potential < 0 || current_pot < best_potential) {
                best_point = current;
                best_potential = current_pot;
            }

            theta += d_theta;
        }

        return best_point;
    }

    Path PF::get_path(Point start, Point goal) {
        return this->get_path(start, goal, 0);
    }

    Path PF::get_path(Point start, Point goal, double t) {
        vector<STPoint> stp_list;
        STPoint current_pt = STPoint(start.get_x(), start.get_y(), t);

        while (current_pt.euclid_dist(goal) > this->goal_radius) {
            for (Agent *ag : this->agents) {
                ag->step(current_pt.get_t());
                ag->update_starting_positions();
            }

            stp_list.push_back(current_pt);
            current_pt = this->get_best_sample(current_pt, goal,
                    current_pt.get_t());
        }

        return Path(stp_list);
    }
}
