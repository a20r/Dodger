
#ifndef AGENT_H
#define AGENT_H

#include <list>
#include "model.hpp"

#define DELTA_T 0.01
#define STD_SCALE 1.5
#define WEIGHT_SCALE 1.0

class Agent {

    public:
        Agent(Model model_x, Model model_y);
        double get_normal_dist(double x, double std);
        Point get_position(double t);
        double get_prob(double x, double y, double t_0, double t_m);
        static double get_probability(double x, double y, double t_0,
                double t_m, std::list<Agent> agents);

    private:
        Model model_x;
        Model model_y;

};

#endif
