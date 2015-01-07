
#ifndef SEARCH_H
#define SEARCH_H

#include <list>
#include <string>
#include <tr1/unordered_map>
#include "roadmap.hpp"
#include "stpoint.hpp"
#include "agent.hpp"
#include "point.hpp"
#include "path.hpp"

#define REPEAT_COST_SCALE 0.1
#define NUM_EDGE_SAMPLES 10
#define COST_SCALE 10
#define GOAL_RADIUS 0.3

namespace Dodger {

    class Search {

        public:
            Search() {};
            Search(Roadmap rm, double speed, double wait_time);
            ~Search() {};
            double get_cost(STPoint n1, STPoint n2, std::list<Agent> agents);
            std::list<STPoint> get_st_neighbours(STPoint node);
            Path get_path(Point s_pt, Point e_pt, std::list<Agent> agents);
            std::list<STPoint>  backtrack_path(
                    std::tr1::unordered_map<std::string, std::string> parents,
                    STPoint goal,
                    std::tr1::unordered_map<std::string, STPoint> decoder);
            static std::string json(Path path, std::list<Agent> agents);

        private:
            Roadmap rm;
            double speed;
            double wait_time;

    };
}

#endif
