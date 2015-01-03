
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

struct Pair PointGrid::transform(Point *p) {
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

void PointGrid::insert(Point p) {
    struct Pair pair = this->transform(&p);
    this->grid[pair.j][pair.i].push_back(p);
}

std::list<Point> PointGrid::get(int i, int j) {
    return this->grid[j][i];
}

std::list<Point> PointGrid::get_nearest(Point p) {
    struct Pair pair = this->transform(&p);
    int diffs[] = {-1, 0, 1};
    std::vector<int> i_diffs(diffs, diffs + sizeof(diffs) / sizeof(int));
    std::vector<int> j_diffs(diffs, diffs + sizeof(diffs) / sizeof(int));

    if (pair.i == 0) {
        i_diffs.erase(i_diffs.begin());
    }
    if (pair.i == this->width - 1) {
        i_diffs.erase(i_diffs.begin() + 2);
    }
    if (pair.j == 0) {
        j_diffs.erase(j_diffs.begin());
    }
    if (pair.j == this->height - 1) {
        j_diffs.erase(j_diffs.begin() + 2);
    }

    std::list<Point> closest;
    std::list<Point> inner;
    for (int p = 0; p < i_diffs.size(); p++) {
        int i_diff = i_diffs[p];
        for (int q = 0; q < j_diffs.size(); q++) {
            int j_diff = j_diffs[q];
            inner = this->get(pair.i + i_diff, pair.j + j_diff);
            closest.insert(closest.end(), inner.begin(), inner.end());
        }
    }

    return closest;
}
