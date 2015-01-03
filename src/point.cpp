
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include "util.hpp"
#include "point.hpp"

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
    this->z = 0;

    std::stringstream buffer;
    buffer << x << " " << y << " " << z;
    this->str_rep = buffer.str();
}

Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::~Point() {

}

double Point::get_x() const {
    return this->x;
}

double Point::get_y() const {
    return this->y;
}

double Point::get_z() const {
    return this->z;
}

void Point::set_x(double x) {
    this->x = x;
}

void Point::set_y(double y) {
    this->y = y;
}

void Point::set_z(double z) {
    this->z = z;
}

double Point::euclid_dist(Point other_point) {

    double px = pow(this->x - other_point.get_x(), 2);
    double py = pow(this->y - other_point.get_y(), 2);
    double pz = pow(this->z - other_point.get_z(), 2);
    return sqrt(px + py + pz);

}

Point Point::to_unit_vector() {
    Point origin(0, 0, 0);
    double mag = this->euclid_dist(origin);
    Point p(this->x / mag, this->y / mag, this->z / mag);
    return p;
}

std::string Point::str() {
    return this->str_rep;
}

bool Point::operator==(Point rhs) {
    return this->str().compare(rhs.str()) == 0;
}

Point Point::get_random_point_2d(double width, double height) {
    double x = rand_float(0, width);
    double y = rand_float(0, height);
    Point p(x, y);
    return p;
}
