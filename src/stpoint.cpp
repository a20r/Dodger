
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

STPoint::~STPoint() {

}

double STPoint::get_t() {
    return this->t;
}

void STPoint::set_t(double t) {
    this->t = t;
}

double STPoint::st_dist(STPoint *other_point) {
    double px = pow(this->x - other_point->get_x(), 2);
    double py = pow(this->y - other_point->get_y(), 2);
    double pz = pow(this->z - other_point->get_z(), 2);
    double pt = pow(this->t - other_point->get_t(), 2);
    return sqrt(px + py + pz + pt);
}
