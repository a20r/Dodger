
#include "point.hpp"
#include <iostream>

int main() {
    Point p1 = Point::get_random_point_2d(5, 5);
    Point p2 = Point::get_random_point_2d(5, 5);
    std::cout << p1.euclid_dist(p2);
    return 0;
}
