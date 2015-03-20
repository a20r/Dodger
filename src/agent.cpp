
#include <iostream>
#include <sstream>
#include <math.h>
#include "point.hpp"
#include "util.hpp"
#include "stpoint.hpp"
#include "agent.hpp"

namespace Dodger {

    Agent::Agent(Model *model_x, Model *model_y, double noise) {
        this->model_x = model_x;
        this->model_y = model_y;
        this->noise = noise;
    }

    Agent::Agent(Model *model_x, Model *model_y) {
        this->model_x = model_x;
        this->model_y = model_y;
        this->noise = 0.0;
    }

    double Agent::get_normal_dist(double x, double std) {
        double coeff = 1.0 / (std * sqrt(2.0 * M_PI));
        double pow_val = exp(-pow(x, 2) / (2.0 * pow(std, 2)));
        return coeff * pow_val;
    }

    Point Agent::get_position(double t) {
        double x = this->model_x->call(t);
        double y = this->model_y->call(t);
        return Point(x, y);
    }

    void Agent::step(double t) {}

    void Agent::update_starting_positions() {}

    double Agent::get_difference(double t) {
        return 0;
    }

    vector<STPoint> Agent::get_path() {
        vector<STPoint> empty;
        return empty;
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
            prob = this->get_normal_dist(dist, STD_SCALE * (t - t_0) + STD_0);
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
        for (Agent *ag : agents) {
            prob_sum += ag->get_prob(x, y, t_0, t_m);
        }

        return prob_sum / agents.size();
    }

    StochasticAgent::StochasticAgent(Model *model_x, Model *model_y,
            Point start, double noise_std) {
        this->model_x = model_x;
        this->model_y = model_y;
        this->start = start;
        this->current_x = start.get_x();
        this->current_y = start.get_y();
        this->holder_x = start.get_x();
        this->holder_y = start.get_y();
        this->holder_t = 0;
        this->current_t = 0;
        this->noise_std = noise_std;
    }

    void StochasticAgent::step(double t) {
        int sample_rate = 100; // per second
        int num_samples = (t - this->current_t) * sample_rate;
        double dt = 1.0 / sample_rate;
        double tc = this->current_t;
        double rx = rand_float(-this->noise_std, this->noise_std);
        double ry = rand_float(-this->noise_std, this->noise_std);

        for (int i = 0; i <= num_samples; i++) {
            this->current_x += this->model_x->call(tc + i * dt) * dt + rx;
            this->current_y += this->model_y->call(tc + i * dt) * dt + rx;

            path_vec.push_back(STPoint(this->current_x, this->current_y,
                        tc + i * dt));
        }

        this->current_t = t;
    }

    double StochasticAgent::get_difference(double t) {
        Point pp = this->get_position(t);
        return sqrt(pow(this->current_x - pp.get_x(), 2)
                + pow(this->current_y - pp.get_y(), 2));
    }

    void StochasticAgent::update_starting_positions() {
        this->holder_x = this->current_x;
        this->holder_y = this->current_y;
        this->holder_t = this->current_t;
    }

    Point StochasticAgent::get_position(double t) {
        // t >= current_t
        int num_samples = 100;
        double dt = (t - this->holder_t) / num_samples;
        double tc = this->holder_t;
        double x = this->holder_x;
        double y = this->holder_y;

        for (int i = 0; i <= num_samples; i++) {
            x += this->model_x->call(tc + i * dt) * dt;
            y += this->model_y->call(tc + i * dt) * dt;
        }

        return Point(x, y);
    }

    vector<STPoint> StochasticAgent::get_path() {
        return this->path_vec;
    }

    std::string StochasticAgent::json() {
        return Path(this->path_vec).json();
    }
}
