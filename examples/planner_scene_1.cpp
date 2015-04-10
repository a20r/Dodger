
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

    double speed = 1.5;
    double wait_time = 0.1;
    double noise_std = 0.000;
    double pred_dev = 0.6;
    double goal_radius = 0.5;
    double width = 4;
    double height = 4;
    double conn_dist = 0.2;
    int num_points = 1000;

    std::list<Dodger::Agent *> agents;

    Dodger::StochasticAgent *ag = new Dodger::StochasticAgent(
        new Dodger::LinearModel(0, 0),
        new Dodger::CosModel(-8, 4, 0, 0),
        Dodger::Point(1, 2), noise_std);

    Dodger::StochasticAgent *ag2 = new Dodger::StochasticAgent(
        new Dodger::LinearModel(0, 0),
        new Dodger::CosModel(-8, 4, 0, 0),
        Dodger::Point(3, 2), noise_std);

    Dodger::StochasticAgent *ag3 = new Dodger::StochasticAgent(
        new Dodger::LinearModel(0, 0),
        new Dodger::CosModel(8, 4, 0, 0),
        Dodger::Point(0, 2), noise_std);

    Dodger::StochasticAgent *ag4 = new Dodger::StochasticAgent(
        new Dodger::LinearModel(0, 0),
        new Dodger::CosModel(8, 4, 0, 0),
        Dodger::Point(4, 2), noise_std);

    Dodger::StochasticAgent *ag5 = new Dodger::StochasticAgent(
        new Dodger::CosModel(10, 5, 0, 0),
        new Dodger::LinearModel(0, 0),
        Dodger::Point(2, 3), noise_std);

    Dodger::StochasticAgent *ag6 = new Dodger::StochasticAgent(
        new Dodger::CosModel(-10, 5, 0, 0),
        new Dodger::LinearModel(0, 0),
        Dodger::Point(2, 2), noise_std);

    Dodger::StochasticAgent *ag7 = new Dodger::StochasticAgent(
        new Dodger::CosModel(10, 5, 0, 0),
        new Dodger::LinearModel(0, 0),
        Dodger::Point(2, 1), noise_std);

    agents.push_back(ag);
    agents.push_back(ag2);
    agents.push_back(ag3);
    agents.push_back(ag4);
    agents.push_back(ag5);
    agents.push_back(ag6);
    agents.push_back(ag7);

    Dodger::Point start(2, 0);
    Dodger::Point goal(2, 4);
    Dodger::RoadmapGenerator rmgr(width, height, start, conn_dist);

    Dodger::Roadmap rm = rmgr.generate(num_points);
    Dodger::Search search(rm, speed, wait_time);
    Dodger::Planner planner(search, agents, goal_radius, pred_dev);

    Dodger::Path path = planner.get_path(start, goal);
    cout << Dodger::Search::json(path, agents) << endl;
}
