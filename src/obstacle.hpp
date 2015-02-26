
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <vector>
#include "point.hpp"

#define LINE_STEP 0.1

using namespace std;
using namespace rapidjson;

namespace Dodger {

    class Obstacle {

        public:
            Obstacle() {};
            ~Obstacle() {};
            Obstacle(vector<Point> points);
            bool in(Point p);
            bool in(Point p_start, Point p_end);
            double strange_index(int i);
            static vector<Obstacle> load_obstacles(string filename);

        private:
            vector<Point> points;
    };

}

#endif
