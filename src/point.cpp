
#include <math.h>
#include <stdlib.h>
#include "point.hpp"

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::~Point() {

}

double Point::get_x() {
    return this->x;
}

double Point::get_y() {
    return this->y;
}

void Point::set_x(double x) {
    this->x = x;
}

void Point::set_y(double y) {
    this->y = y;
}

double Point::euclid_dist(Point* other_point) {

    double px = pow(this->x - other_point->get_x(), 2);
    double py = pow(this->y - other_point->get_y(), 2);
    return sqrt(px + py);

}

Point* Point::to_unit_vector() {
    double mag = this->euclid_dist(new Point(0, 0));
    return new Point(this->x / mag, this->y / mag);
}
