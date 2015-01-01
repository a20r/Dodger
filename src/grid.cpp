
#include <list>
#include <vector>
#include "point.hpp"
#include "grid.hpp"

PointGrid::PointGrid(const int width, const int height,
        double a_width, double a_height) {
    this->width = width;
    this->height = height;
    this->a_width = a_width;
    this->a_height = a_height;
    this->grid.resize(height);
    for (int i = 0; i < height; i++) {
        this->grid[i].resize(width);
    }
}

PointGrid::~PointGrid() {

}

int PointGrid::map_val(double x, double in_min, double in_max,
        int out_min, int out_max) {

    return (int) (x - in_min) * (out_max - out_min) / (in_max - in_min)
        + out_min;
}

Pair PointGrid::transform(Point *p) {
    int i, j;
    i = j = -1;

    if (p->get_x() >= this->a_width) {
        i = this->width - 1;
    } else if (p->get_x() < 0) {
        i = 0;
    }

    if (p->get_y() >= this->a_height) {
        j = this->height - 1;
    } else if (p->get_y() < 0) {
        j = 0;
    }

    if (i < 0) {
        i = this->map_val(p->get_x(), 0, this->a_width, 0, this->width - 1);
    }

    if (j < 0) {
        j = this->map_val(p->get_y(), 0, this->a_height, 0, this->height - 1);
    }

    struct Pair pair;
    pair.i = i;
    pair.j = j;

    return pair;
}
