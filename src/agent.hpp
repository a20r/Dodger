
#ifndef AGENT_H
#define AGENT_H

#include <list>
#include <cmath>
#include "path.hpp"
#include "model.hpp"

#define DELTA_T 0.01
#define STD_SCALE 1.0
#define WEIGHT_SCALE 1.5
#define STD_0 0.2

#define T_STEP 0.1 // used for the path generation
#define RAND_STD 0.1
#define MAX_TIME 50

namespace Dodger {

    class Agent {

        public:
            Agent() {};
            Agent(Model *model_x, Model *model_y, double noise);
            Agent(Model *model_x, Model *model_y);
            ~Agent() {};
            double get_normal_dist(double x, double std);
            virtual Point get_position(double t);
            double get_prob(double x, double y, double t_0, double t_m);
            virtual std::string json();
            static double get_probability(double x, double y, double t_0,
                    double t_m, std::list<Agent *> agents);

        protected:
            double noise;
            Model *model_x;
            Model *model_y;

    };

    class StochasticAgent : public Agent {

        public:
            StochasticAgent() {};
            StochasticAgent(Model *model_x, Model *model_y, Point start);
            ~StochasticAgent() {};
            Point get_position(double t);
            Point get_path();
            std::string json();

        private:
            Path generate_path(double max_time);

        protected:
            Model *model_x;
            Model *model_y;
            Point start;
            Path path;
            double current_x, current_y;
            double current_t;
    };
}
#endif
