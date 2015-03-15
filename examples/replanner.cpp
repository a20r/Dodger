
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
        new Dodger::CosModel(6, 3, 1, 0),
        new Dodger::LinearModel(0, 0),
        Dodger::Point(3.68, 1), noise_std);

    Dodger::StochasticAgent *ag2 = new Dodger::StochasticAgent(
        new Dodger::CosModel(-6, 3, 1, 0),
        new Dodger::LinearModel(0, 0),
        Dodger::Point(0.32, 2), noise_std);


    Dodger::StochasticAgent *ag3 = new Dodger::StochasticAgent(
        new Dodger::CosModel(6, 3, 1, 0),
        new Dodger::LinearModel(0, 0),
        Dodger::Point(3.68, 3), noise_std);

    agents.push_back(ag);
    agents.push_back(ag2);
    agents.push_back(ag3);

    Dodger::Point start(2, 0);
    Dodger::Point goal(2, 4);
    Dodger::RoadmapGenerator rmgr(4, 4, start, 0.2);

    Dodger::Roadmap rm = rmgr.generate(1000);
    Dodger::Search search(rm, speed, wait_time);
    Dodger::Planner planner(search, agents, 0.5, 0.6);

    Dodger::Path path = planner.get_path(start, goal);
    cout << Dodger::Search::json(path, agents) << endl;
}
