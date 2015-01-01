
#include <math.h>
#include "model.hpp"

double LinearModel::call(double t) {
    return this->m * t + this->b;
}

double SinModel::call(double t) {
    return this->a * sin(this->b * t + this->c) + this->d;
}
