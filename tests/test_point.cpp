
#include "point.hpp"
#include <iostream>

int main() {
    Point *p1 = new Point(1, 1);
    Point *p2 = new Point(2, 2);
    std::cout << p1->euclid_dist(p2);
    return 0;
}
