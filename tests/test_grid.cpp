
#include <iostream>
#include <list>
#include "stpoint.hpp"
#include "grid.hpp"

int main() {

    Dodger::PointGrid pg(5, 5, 5, 5);
    Dodger::STPoint p_in(6, 6, 1);
    Dodger::STPoint p_check(5, 5, 2);
    pg.insert(p_in);
    pg.insert(p_in);
    std::list<Dodger::Point> closest = pg.get_nearest(p_check);
    std::list<Dodger::Point>::const_iterator iterator;
    for (iterator = closest.begin(); iterator != closest.end(); ++iterator) {
        std::cout << (*iterator).get_x() << " ";
        std::cout << (*iterator).get_y() << std::endl;
    }
    return 0;
}
