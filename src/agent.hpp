
#ifndef AGENT_H
#define AGENT_H

#include <list>
#include <cmath>
#include <random>
#include "path.hpp"
#include "model.hpp"

#define DELTA_T 0.01
#define STD_SCALE 1.0
#define WEIGHT_SCALE 1.5
#define STD_0 0.2

#define T_STEP 0.1 // used for the path generation
#define RAND_STD 0.1
#define MAX_TIME 50

using namespace std;

namespace Dodger {

    class Agent {

        public:
            Agent() {};
            Agent(Model *model_x, Model *model_y, double noise);
            Agent(Model *model_x, Model *model_y);
            ~Agent() {};
            double get_normal_dist(double x, double std);
            virtual Point get_position(double t);
            virtual void step(double t);
            virtual double get_difference(double t);
            virtual void update_starting_positions();
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
            StochasticAgent(Model *model_x, Model *model_y, Point start,
                    double noise_std);
            ~StochasticAgent() {};
            void step(double t);
            double get_difference(double t);
            void update_starting_positions();
            Point get_position(double t);
            std::string json();

        protected:
            Model *model_x;
            Model *model_y;
            Point start;
            Path path;
            double current_x, current_y;
            double holder_x, holder_y;
            double current_t, holder_t;
            default_random_engine generator;
            normal_distribution<double> distribution;
            vector<STPoint> path_vec;

    };
}
#endif
