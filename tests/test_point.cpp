
#include "point.hpp"
#include <iostream>

int main() {
    Dodger::Point p1 = Dodger::Point::get_random_point_2d(5, 5);
    Dodger::Point p2 = Dodger::Point::get_random_point_2d(5, 5);
    std::cout << p1.euclid_dist(p2);
    return 0;
}
