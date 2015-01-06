
#include <iostream>
#include <set>
#include "point.hpp"
#include "roadmap.hpp"
#include "rmgenerator.hpp"

int main() {

    Dodger::Point start(2, 0);
    Dodger::RoadmapGenerator rmgr(5, 5, start, 0.3);
    Dodger::Roadmap rm = rmgr.generate(500);

    std::set<std::string>::iterator iterator;
    std::set<std::string> nodes = rm.get_nodes();
    std::set<std::string>::iterator n_iterator;
    std::set<std::string> neighs;

    for (iterator = nodes.begin(); iterator != nodes.end(); ++iterator) {
        if (rm.decode((*iterator)).get_x() == 2) {
            neighs = rm.get_neighbours(*iterator);
            std::cout << *iterator << std::endl;
            for (n_iterator = neighs.begin(); n_iterator != neighs.end();
                    ++n_iterator) {
                std::cout << "\t" << *n_iterator << std::endl;
            }
        }
    }

    return 0;
}
