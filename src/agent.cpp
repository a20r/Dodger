
#include <iostream>
#include <sstream>
#include <math.h>
#include "point.hpp"
#include "stpoint.hpp"
#include "agent.hpp"

namespace Dodger {

    Agent::Agent(Model *model_x, Model *model_y) {
        this->model_x = model_x;
        this->model_y = model_y;
    }

    double Agent::get_normal_dist(double x, double std) {
        double coeff = 1.0 / (std * sqrt(2.0 * M_PI));
        double pow_val = exp(-pow(x, 2) / (2.0 * pow(std, 2)));
        return coeff * pow_val;
    }

    Point Agent::get_position(double t) {
        double x = this->model_x->call(t);
        double y = this->model_y->call(t);
        Point p(x, y);
        return p;
    }

    double Agent::get_prob(double x, double y, double t_0, double t_m) {
        double t = t_0;
        double prob_sum = 0.0;
        double num_samples = 0;
        Point current(x, y);
        Point pos;
        double dist, prob;

        while (t <= t_m) {
            num_samples++;
            pos = this->get_position(t);
            dist = pos.euclid_dist(current);
            prob = this->get_normal_dist(dist, STD_SCALE * (t - t_0) + 0.1);
            prob_sum += pow(t_m - t + 1, WEIGHT_SCALE) * prob;
            t += DELTA_T;
        }

        return prob_sum / num_samples;
    }

    std::string Agent::json() {
        std::stringstream buffer;
        buffer << "{\"x\":" << this->model_x->json() <<
            ",\"y\":" << this->model_y->json() << "}";
        return buffer.str();
    }

    double Agent::get_probability(double x, double y, double t_0, double t_m,
            std::list<Agent *> agents) {

        double prob_sum = 0.0;
        std::list<Agent *>::iterator iterator;
        for (iterator = agents.begin(); iterator != agents.end(); ++iterator) {
            prob_sum += (*iterator)->get_prob(x, y, t_0, t_m);
        }

        return prob_sum / agents.size();
    }

    StochasticAgent::StochasticAgent(Model *model_x, Model *model_y,
            Point start) {
        this->model_x = model_x;
        this->model_y = model_y;
        this->start = start;
        this->path = this->generate_path(MAX_TIME);
    }

    Path StochasticAgent::generate_path(double max_time) {
        double last_x = this->start.get_x();
        double last_y = this->start.get_y();
        double x, y, t;
        std::list<STPoint> path;
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(0, RAND_STD);

        path.push_back(STPoint(last_x, last_y, 0));
        t = T_STEP;

        while (t < max_time) {
            x = last_x + this->model_x->call(t) * T_STEP;
            y = last_y + this->model_y->call(t) * T_STEP;
            path.push_back(STPoint(x, y, t));
            t += T_STEP;
        }

        return Path(path);
    }

    Point StochasticAgent::get_position(double t) {
        return this->path.get_position(t);
    }

    std::string StochasticAgent::json() {
        return this->path.json();
    }
}
