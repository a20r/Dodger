
#ifndef AGENT_H
#define AGENT_H

#include <list>
#include "model.hpp"

#define DELTA_T 0.01
#define STD_SCALE 1.0
#define WEIGHT_SCALE 1.5

namespace Dodger {

    class Agent {

        public:
            Agent() {};
            Agent(Model *model_x, Model *model_y);
            ~Agent() {};
            double get_normal_dist(double x, double std);
            Point get_position(double t);
            double get_prob(double x, double y, double t_0, double t_m);
            std::string json();
            static double get_probability(double x, double y, double t_0,
                    double t_m, std::list<Agent *> agents);

        protected:
            Model *model_x;
            Model *model_y;

    };

    class StochasticAgent : public Agent {

        public:
            StochasticAgent() {};
            StochasticAgent(Point start, Model *model_x, Model *model_y);
            ~StochasticAgent() {};
            Point get_position(double t);
            double get_prob(double x, double y, double t_0, double t_m);
            std::string json();

        protected:
            Model *model_x;
            Model *model_y;
    };

}
#endif
