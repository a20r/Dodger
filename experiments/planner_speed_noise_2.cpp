
#include <iostream>
#include <iterator>
#include <list>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <time.h>
#include <utility>
#include "dodger.hpp"

int main() {

    const int num_speeds = 8;
    double speeds [num_speeds] = {1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5};

    const int num_noises = 6;
    double noises [num_noises] = {0.0, 0.002, 0.004, 0.006, 0.008, 0.01};

    const int num_runs = 20;
    double min_distances [num_runs];
    double avg_min_distances [num_runs];
    double times [num_runs];
    double max_costs [num_runs];
    double avg_costs [num_runs];


    double wait_time = 0.1;
    double pred_dev = 0.6;
    double goal_radius = 0.5;
    double width = 4;
    double height = 4;
    double conn_dist = 0.2;
    int num_points = 1000;

    cout << "speed" << ", ";
    cout << "noise" << ", ";
    cout << "mean_min_distance" << ", ";
    cout << "std_min_distance" << ", ";
    cout << "mean_avg_min_distance" << ", ";
    cout << "std_avg_min_distance" << ", ";
    cout << "avg_times" << ", ";
    cout << "std_times" << ", ";
    cout << "mean_max_cost" << ", ";
    cout << "std_max_cost" << ", ";
    cout << "mean_avg_cost" << ", ";
    cout << "std_avg_cost" << endl;

    Dodger::Point start(2, 0);
    Dodger::Point goal(2, 4);
    Dodger::RoadmapGenerator rmgr(width, height, start, conn_dist);
    Dodger::Roadmap rm = rmgr.generate(num_points);

    for (int i = 0; i < num_speeds; i++) {
        for (int j = 0; j < num_noises; j++) {
            double speed = speeds[i];
            double noise_std = noises[j];

            for (int k = 0; k < num_runs; k++) {
                srand(k);
                cerr << speed << ", " << noise_std << ", " << k << endl;
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

                Dodger::Search search(rm, speed, wait_time);
                Dodger::Planner planner(search, agents, goal_radius, pred_dev);

                s_time = std::clock();
                Dodger::Path path = planner.get_path(start, goal);
                duration = (std::clock() - s_time) / (double) CLOCKS_PER_SEC;

                min_distances[k] = Dodger::Stats::min_distance(path, agents);
                avg_min_distances[k] = Dodger::Stats::avg_min_distance(path,
                        agents);
                times[k] = duration;

                pair<double, double> costs = Dodger::Stats::costs(path, agents);
                max_costs[k] = get<0>(costs);
                avg_costs[k] = get<1>(costs);

            }

            cout << speed << ", ";
            cout << noise_std << ", ";
            cout << Dodger::Stats::mean(min_distances, num_runs) << ", ";
            cout << Dodger::Stats::std(min_distances, num_runs) << ", ";
            cout << Dodger::Stats::mean(avg_min_distances, num_runs) << ", ";
            cout << Dodger::Stats::std(avg_min_distances, num_runs) << ", ";
            cout << Dodger::Stats::mean(times, num_runs) << ", ";
            cout << Dodger::Stats::std(times, num_runs) << ", ";
            cout << Dodger::Stats::mean(max_costs, num_runs) << ", ";
            cout << Dodger::Stats::std(max_costs, num_runs) << ", ";
            cout << Dodger::Stats::mean(avg_costs, num_runs) << ", ";
            cout << Dodger::Stats::std(avg_costs, num_runs) << endl;

        }
    }
}
