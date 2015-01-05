
#include <iostream>
#include <math.h>
#include "point.hpp"
#include "agent.hpp"

Agent::Agent(Model model_x, Model model_y) {
    this->model_x = model_x;
    this->model_y = model_y;
}

double Agent::get_normal_dist(double x, double std) {
    double coeff = 1.0 / (std * sqrt(2.0 * M_PI));
    double pow_val = exp(-pow(x, 2) / (2.0 * pow(std, 2)));
    return coeff * pow_val;
}

Point Agent::get_position(double t) {
    double x = this->model_x.call(t);
    double y = this->model_y.call(t);
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

double Agent::get_probability(double x, double y, double t_0, double t_m,
        std::list<Agent> agents) {

    double prob_sum = 0.0;
    Agent current;
    std::list<Agent>::const_iterator iterator;
    for (iterator = agents.begin(); iterator != agents.end(); ++iterator) {
        current = *iterator;
        prob_sum += current.get_prob(x, y, t_0, t_m);
    }

    return prob_sum / agents.size();
}
