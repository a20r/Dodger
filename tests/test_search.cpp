
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

int main() {

    srand(time(NULL));

    double speed = 2;
    double wait_time = 0.1;
    std::list<Dodger::Agent> agents;

    Dodger::Agent ag(
        new Dodger::SinModel(2, 3, 1, 2),
        new Dodger::LinearModel(0, 1));

    Dodger::Agent ag2(
        new Dodger::SinModel(-2, 2, 1, 2),
        new Dodger::LinearModel(0, 1.3));

    Dodger::Agent ag3(
        new Dodger::SinModel(2, 2.5, 1, 2),
        new Dodger::LinearModel(0, 1.8));

    Dodger::Agent ag4(
        new Dodger::SinModel(-2, 3, 1, 2),
        new Dodger::LinearModel(0, 2.1));

    Dodger::Agent ag5(
        new Dodger::SinModel(2, 4, 1, 2),
        new Dodger::LinearModel(0, 2.5));

    Dodger::Agent ag6(
        new Dodger::SinModel(-2, 5, 1, 2),
        new Dodger::LinearModel(0, 3));


    agents.push_back(ag);
    agents.push_back(ag2);
    agents.push_back(ag3);
    agents.push_back(ag4);
    agents.push_back(ag5);
    agents.push_back(ag6);

    Dodger::Point start(2, 0);
    Dodger::Point goal(2, 4);
    Dodger::RoadmapGenerator rmgr(4, 4, start, 0.3);
    Dodger::Roadmap rm = rmgr.generate(1000);

    Dodger::Search search(rm, speed, wait_time);
    Dodger::Path path = search.get_path(start, goal, agents);
    std::cout << Dodger::Search::json(path, agents) << std::endl;

}
