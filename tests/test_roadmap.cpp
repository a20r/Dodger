
#include <iostream>
#include "point.hpp"
#include "roadmap.hpp"
#include "rmgenerator.hpp"

int main() {

    Point start(2, 0);
    RoadmapGenerator rmgr(5, 5, start, 0.3);
    Roadmap rm = rmgr.generate(500);
    std::cout << rm.get_nodes().size() << std::endl;
    return 0;
}
