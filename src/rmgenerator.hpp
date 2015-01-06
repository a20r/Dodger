
#ifndef ROADMAP_GENERATOR_H
#define ROADMAP_GENERATOR_H

#include "point.hpp"

namespace Dodger {

    class RoadmapGenerator {

        public:
            RoadmapGenerator(double width, double height, Point start,
                    double max_dist);
            ~RoadmapGenerator() {};
            Roadmap resample(Roadmap rm, int num_points);
            Roadmap generate(int num_points);

        private:
            double width;
            double height;
            double max_dist;
            Point start;

    };
}

#endif
