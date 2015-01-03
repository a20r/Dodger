
#include <iostream>
#include "stpoint.hpp"

int main() {
    STPoint p1(1, 1, 0);
    STPoint p2(2, 2, 1);
    std::cout << p1.euclid_dist(p2);
    return 0;
}
