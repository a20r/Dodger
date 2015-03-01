
#include <fstream>
#include "obstacle.hpp"

namespace Dodger {

    Obstacle::Obstacle(vector<Point> points) {
        this->points = points;
    }

    double Obstacle::strange_index(int i) {
        int actual_index = i / 2;
        if (i % 2 == 0) {
            return this->points[actual_index].get_x();
        } else {
            return this->points[actual_index].get_y();
        }
    }

    bool Obstacle::in(Point p) {
        // Please do not look at this code. I have no idea how it works.
        int i, i1, lcross = 0, rcross = 0;
        double px = p.get_x();
        double py = p.get_y();
        double x = 0.0;
        int n = this->points.size();
        bool testr;
        bool testl;

        for(i = 0; i < n; i++)
        {
            if (strange_index(2 * i) == px && strange_index(2 * i + 1) == py) {
                return true;
            }

            i1 = (i + n - 1) % n;

            testr = (strange_index(2 * i + 1) > py)
                != (strange_index(2 * i1 + 1) > py);
            testl = (strange_index(2 * i + 1) < py)
                != (strange_index(2 * i1 + 1) < py);

            if (testr || testl) {
                x = (strange_index(2 * i) * strange_index(2 * i1 + 1)
                        - strange_index(2 * i1) * strange_index(2 * i + 1)
                        + py * (strange_index(2 * i1)
                            - strange_index(2 * i)))
                        / (strange_index(2 * i1 + 1)
                            - strange_index(2 * i + 1));
            }

            if (testr && x > px) {
                rcross++;
            }

            if (testl && x < px) {
                lcross++;
            }
        }

        if ((rcross & 1) != (lcross & 1)) {
            return true;
        }

        return (rcross & 1);
    }

    bool Obstacle::in(Point p_start, Point p_end) {
        return false;
    }

    bool Obstacle::in_any(Point p, list<Obstacle> obs) {
        for (Obstacle ob : obs) {
            if (ob.in(p)) {
                return true;
            }
        }

        return false;
    }
}
