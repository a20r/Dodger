
#ifndef STATS_H
#define STATS_H

#include "path.hpp"
#include "agent.hpp"

namespace Dodger {

    class Stats {
        public:
            static double avg_min_distance(Path path, list<Agent *> ags);
            static double min_distance(Path path, list<Agent *> ags);
    };

}

#endif
