
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include <list>
#include "point.hpp"

#define LINE_STEP 0.1

using namespace std;

namespace Dodger {

    class Obstacle {

        public:
            Obstacle() {};
            ~Obstacle() {};
            Obstacle(vector<Point> points);
            bool in(Point p);
            bool in(Point p_start, Point p_end);
            double strange_index(int i);
            static bool in_any(Point p, list<Obstacle> obs);

        private:
            vector<Point> points;
    };

}

#endif
