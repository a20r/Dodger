#ifndef PLANNER_H
#define PLANNER_H

#include <list>
#include "agent.hpp"
#include "point.hpp"
#include "roadmap.hpp"
#include "path.hpp"
#include "search.hpp"

using namespace std;

namespace Dodger {

    class Planner {

        public:
            Planner() {};
            ~Planner() {};
            Planner(Search search, list<Agent *> agents,
                    double goal_radius, double pred_dev);
            Path get_path(Point start, Point goal);

        private:
            Search search;
            list<Agent *> agents;
            double goal_radius;
            double pred_dev;
    };
}

#endif
