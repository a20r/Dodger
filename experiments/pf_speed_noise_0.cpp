
#include <iostream>
#include <iterator>
#include <list>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <time.h>
#include "dodger.hpp"

int main() {

    srand(time(NULL));

    const int num_speeds = 4;
    double speeds [num_speeds] = {1, 1.5, 2, 2.5};

    const int num_noises = 6;
    double noises [num_noises] = {0.0, 0.002, 0.004, 0.006, 0.008, 0.01};

    int num_samples = 20;
    double dt = 0.07;
    double goal_radius = 0.5;
    double width = 4;
    double height = 4;
    int num_points = 1000;

    for (int i = 0; i < num_speeds; i++) {
        for (int j = 0; j < num_noises; j++) {
            double speed = speeds[i];
            double noise_std = noises[j];

            std::list<Dodger::Agent *> agents;

            Dodger::StochasticAgent *ag = new Dodger::StochasticAgent(
                new Dodger::CosModel(6, 3, 1, 0),
                new Dodger::LinearModel(0, 0),
                Dodger::Point(3.68, 0.5), noise_std);

            Dodger::StochasticAgent *ag2 = new Dodger::StochasticAgent(
                new Dodger::CosModel(-6, 3, 1, 0),
                new Dodger::LinearModel(0, 0),
                Dodger::Point(0.32, 1), noise_std);

            Dodger::StochasticAgent *ag3 = new Dodger::StochasticAgent(
                new Dodger::CosModel(6, 3, 1, 0),
                new Dodger::LinearModel(0, 0),
                Dodger::Point(3.68, 1.5), noise_std);

            Dodger::StochasticAgent *ag4 = new Dodger::StochasticAgent(
                new Dodger::CosModel(-6, 3, 1, 0),
                new Dodger::LinearModel(0, 0),
                Dodger::Point(0.32, 2), noise_std);

            Dodger::StochasticAgent *ag5 = new Dodger::StochasticAgent(
                new Dodger::CosModel(6, 3, 1, 0),
                new Dodger::LinearModel(0, 0),
                Dodger::Point(3.68, 2.5), noise_std);

            Dodger::StochasticAgent *ag6 = new Dodger::StochasticAgent(
                new Dodger::CosModel(-6, 3, 1, 0),
                new Dodger::LinearModel(0, 0),
                Dodger::Point(0.32, 3), noise_std);

            agents.push_back(ag);
            agents.push_back(ag2);
            agents.push_back(ag3);
            agents.push_back(ag4);
            agents.push_back(ag5);
            agents.push_back(ag6);

            std::clock_t s_time;
            double duration;

            Dodger::Point start(2, 0);
            Dodger::Point goal(2, 4);

            Dodger::PF pf(agents, goal_radius, speed, dt, num_samples);

            s_time = std::clock();
            Dodger::Path path = pf.get_path(start, goal);
            duration = (std::clock() - s_time) / (double) CLOCKS_PER_SEC;

            cout << speed << ", ";
            cout << noise_std << ", ";
            cout << Dodger::Stats::min_distance(path, agents) << ", ";
            cout << Dodger::Stats::avg_min_distance(path, agents) << ", ";
            cout << duration << endl;
        }
    }
}
