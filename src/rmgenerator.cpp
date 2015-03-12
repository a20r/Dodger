
#include "grid.hpp"
#include "roadmap.hpp"
#include <iostream>
#include "rmgenerator.hpp"

namespace Dodger {

    RoadmapGenerator::RoadmapGenerator(double width, double height, Point start,
            double max_dist) {
        this->width = width;
        this->height = height;
        this->start = start;
        this->max_dist = max_dist;
    }

    RoadmapGenerator::RoadmapGenerator(double width, double height, Point start,
            double max_dist, list<Obstacle> obs) {
        this->width = width;
        this->height = height;
        this->start = start;
        this->max_dist = max_dist;
        this->obs = obs;
    }

    Roadmap RoadmapGenerator::resample(Roadmap rm, int num_points) {
        rm.insert(this->start);
        Point sample;
        for (int i = 0; i < num_points; i++) {
            sample = Point::get_random_point_2d(this->width, this->height);
            if (!Obstacle::in_any(sample, this->obs)) {
                rm.insert(sample);
            }
        }

        return rm;
    }

    Roadmap RoadmapGenerator::generate(int num_points) {
        PointGrid gd(this->width, this->height, this->width, this->height);
        Roadmap rm(gd, this->max_dist);
        return this->resample(rm, num_points);
    }
}
