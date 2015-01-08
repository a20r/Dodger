
#include <sstream>
#include <queue>
#include <iostream>
#include "search.hpp"

namespace Dodger {

    Search::Search(Roadmap rm, double speed, double wait_time) {
        this->rm = rm;
        this->speed = speed;
        this->wait_time = wait_time;
    }

    double Search::get_cost(STPoint n1, STPoint n2, std::list<Agent *> agents) {

        double max_cost = 0;
        double x_slope = (n2.get_x() - n1.get_x()) / NUM_EDGE_SAMPLES;
        double y_slope = (n2.get_y() - n1.get_y()) / NUM_EDGE_SAMPLES;
        double x, y, cost;

        for (int i = 0; i < NUM_EDGE_SAMPLES + 1; i++) {
            x = n1.get_x() + i * x_slope;
            y = n1.get_y() + i * y_slope;
            cost = Agent::get_probability(x, y, n1.get_t(),
                    n2.get_t(), agents);

            if (cost > max_cost) {
                max_cost = cost;
            }
        }

        return max_cost;
    }

    std::list<STPoint> Search::get_st_neighbours(STPoint node) {
        Point current;
        double dist, t;
        std::list<STPoint> st_neighbours;
        std::set<std::string> neighbours = this->rm.get_neighbours(
                node.to_point());
        STPoint wait_node(node.get_x(), node.get_y(),
                node.get_t() + this->wait_time);
        st_neighbours.push_back(wait_node);
        std::set<std::string>::iterator iterator;

        for (iterator = neighbours.begin(); iterator != neighbours.end();
                ++iterator) {
            current = rm.decode(*iterator);
            dist = node.euclid_dist(current);
            t = dist / this->speed + node.get_t();
            STPoint next(current.get_x(), current.get_y(), t);
            st_neighbours.push_back(next);
        }

        return st_neighbours;
    }

    Path Search::get_path(Point s_pt, Point e_pt, std::list<Agent *> agents) {

        this->rm.insert(s_pt);
        this->rm.insert(e_pt);

        std::list<STPoint> neighbours;
        std::tr1::unordered_map<std::string, int> num_visited;
        std::tr1::unordered_map<std::string, STPoint> decoder;
        std::tr1::unordered_map<std::string, std::string> parents;
        std::priority_queue<STPointWeight> open_set;
        STPoint first(s_pt.get_x(), s_pt.get_y(), 0);
        STPointWeight first_weight(first, 0);

        open_set.push(first_weight);
        STPointWeight current;
        Point nr_pt;
        double nr_cost, r_cost, total_cost;

        while (!open_set.empty()) {
            current = open_set.top();
            open_set.pop();
            decoder[current.get_val().str()] = current.get_val();
            if (current.get_val().euclid_dist(e_pt) < GOAL_RADIUS) {
                std::list<STPoint> path = this->backtrack_path(parents,
                        current.get_val(), decoder);
                return Path(path, -current.get_weight());
            }

            neighbours = this->get_st_neighbours(current.get_val());
            std::list<STPoint>::iterator iterator;
            for (iterator = neighbours.begin(); iterator != neighbours.end();
                    ++iterator) {

                parents[(*iterator).str()] = current.get_val().str();
                nr_pt = (*iterator).to_point();

                nr_cost = COST_SCALE * this->get_cost(current.get_val(),
                        *iterator, agents);

                if (num_visited.count(nr_pt.str()) > 0) {
                    r_cost = REPEAT_COST_SCALE * num_visited[nr_pt.str()];
                    num_visited[nr_pt.str()]++;
                } else {
                    r_cost = 0;
                    num_visited[nr_pt.str()] = 1;
                }

                total_cost = nr_cost + r_cost;
                STPointWeight pw(*iterator, -total_cost);
                open_set.push(pw);
            }
        }
    }

    std::list<STPoint> Search::backtrack_path(
            std::tr1::unordered_map<std::string, std::string> parents,
            STPoint goal, std::tr1::unordered_map<std::string, STPoint> decoder) {

        std::list<STPoint> path_list;

        path_list.push_front(goal);
        STPoint current = decoder[parents[goal.str()]];

        while (true) {
            path_list.push_front(current);
            if (parents.count(current.str()) == 0) {
                return path_list;
            } else {
                current = decoder[parents[current.str()]];
            }
        }
    }

    std::string Search::json(Path path, std::list<Agent*> agents) {

        std::list<Agent *>::iterator iterator;
        std::stringstream buffer;
        buffer << "{\"agents\": [";
        int i = 0;
        for (iterator = agents.begin(); iterator != agents.end();
                ++iterator) {
            buffer << (*iterator)->json();
            if (i++ < agents.size() - 1) {
                buffer << ",";
            }
        }

        buffer << "],";
        buffer << "\"path_cost\": " << path.get_cost() << ",";
        buffer << "\"path\": " << path.json() << "}";
        return buffer.str();

    }
}
