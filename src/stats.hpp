
#ifndef STATS_H
#define STATS_H

#include "path.hpp"
#include "agent.hpp"
#include "stpoint.hpp"

namespace Dodger {

    class Stats {
        public:
            static double avg_min_distance(Path path, list<Agent *> ags);
            static double min_distance(Path path, list<Agent *> ags);
            static double mean(double arr[], int size);
            static double std(double arr[], int size);
            static pair<double, double> costs(Path path, list<Agent *> ags);
    };

}

#endif
