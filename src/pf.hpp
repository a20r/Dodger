#ifndef PF_H
#define PF_H

#include <list>
#include <math.h>
#include "agent.hpp"
#include "point.hpp"
#include "path.hpp"

#define MIN_DIST 0.1

using namespace std;

namespace Dodger {

    class PF {

        public:
            PF() {};
            ~PF() {};
            PF(list<Agent *> agents, double goal_radius, double speed,
                    double dt, int num_samples);
            Path get_path(Point start, Point goal, double t);
            Path get_path(Point start, Point goal);

        protected:
            double goal_potential(Point position, Point goal);
            double obstacle_potential(Point position, double t);
            double get_potential(Point position, Point goal, double t);
            STPoint get_best_sample(Point position, Point goal, double t);

        private:
            list<Agent *> agents;
            double goal_radius;
            double speed;
            double dt;
            int num_samples;
    };
}

#endif
