
#ifndef ROADMAP_GENERATOR_H
#define ROADMAP_GENERATOR_H

#include <list>
#include "point.hpp"
#include "obstacle.hpp"

namespace Dodger {

    class RoadmapGenerator {

        public:
            RoadmapGenerator(double width, double height, Point start,
                    double max_dist);
            RoadmapGenerator(double width, double height,
                    Point start, double max_dist, list<Obstacle> obs);
            ~RoadmapGenerator() {};
            Roadmap resample(Roadmap rm, int num_points);
            Roadmap generate(int num_points);

        private:
            double width;
            double height;
            double max_dist;
            Point start;
            list<Obstacle> obs;

    };
}

#endif
