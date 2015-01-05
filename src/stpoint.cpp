
#include <sstream>
#include <iomanip>
#include "math.h"
#include "stpoint.hpp"

STPoint::STPoint(double x, double y, double z, double t) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
}

STPoint::STPoint(double x, double y, double t) {
    this->x = x;
    this->y = y;
    this->z = 0;
    this->t = t;
}

double STPoint::get_t() const {
    return this->t;
}

void STPoint::set_t(double t) {
    this->t = t;
}

std::string STPoint::str() {
    int precision = 4;
    std::stringstream buffer;
    buffer << std::setprecision(precision) << this->x
        << " " << std::setprecision(precision) << this->y
        << " " << std::setprecision(precision) << this->z
        << " " << std::setprecision(precision) << this->t;
    return buffer.str();
}

double STPoint::st_dist(STPoint *other_point) {
    double px = pow(this->x - other_point->get_x(), 2);
    double py = pow(this->y - other_point->get_y(), 2);
    double pz = pow(this->z - other_point->get_z(), 2);
    double pt = pow(this->t - other_point->get_t(), 2);
    return sqrt(px + py + pz + pt);
}

Point STPoint::to_point() {
    Point p(this->x, this->y, this->z);
    return p;
}

std::string STPoint::json() {
    std::stringstream buffer;
    buffer << "{\"x\": " << this->x << ",\"y\": " << this->y
        << ",\"z\": " << this->z << ",\"t\": " << this->t
        << "}";
    return buffer.str();
}

STPointWeight::STPointWeight(STPoint val, double weight) {
    this->val = val;
    this->weight = weight;
}

STPoint STPointWeight::get_val() const {
    return this->val;
}

double STPointWeight::get_weight() const {
    return this->weight;
}

bool STPointWeight::operator<(const STPointWeight& right) const {
    return this->weight < right.get_weight();
}
