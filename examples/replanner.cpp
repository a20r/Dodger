
#include <iostream>
#include <iterator>
#include <list>
#include <stdlib.h>
#include <time.h>
#include "point.hpp"
#include "roadmap.hpp"
#include "rmgenerator.hpp"
#include "model.hpp"
#include "agent.hpp"
#include "path.hpp"
#include "search.hpp"
#include "planner.hpp"

int main() {

    srand(time(NULL));

    double speed = 2.5;
    double wait_time = 0.1;
    double noise_std = 0.1;
    std::list<Dodger::Agent *> agents;

    Dodger::StochasticAgent *ag = new Dodger::StochasticAgent(
        new Dodger::SinModel(6, 3, 1, 0),
        new Dodger::LinearModel(0, 0),
        Dodger::Point(1, 2), noise_std);

    agents.push_back(ag);

    Dodger::Point start(2, 0);
    Dodger::Point goal(2, 4);
    Dodger::RoadmapGenerator rmgr(4, 4, start, 0.2);

    Dodger::Roadmap rm = rmgr.generate(1000);
    Dodger::Search search(rm, speed, wait_time);
    Dodger::Planner planner(search, agents, 0.5, 0.7);

    Dodger::Path path = planner.get_path(start, goal);
    cout << Dodger::Search::json(path, agents) << endl;
}
