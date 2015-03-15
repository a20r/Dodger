
#include <sstream>
#include <math.h>
#include "model.hpp"

namespace Dodger {

    double LinearModel::call(double t) {
        return this->a * t + this->b;
    }

    std::string LinearModel::json() {
        std::stringstream buffer;
        buffer << "{\"type\": \"Linear\", \"params\": [" <<
            this->a << "," << this->b
            << "]}";
        return buffer.str();
    }

    double SinModel::call(double t) {
        return this->a * sin(this->b * t + this->c) + this->d;
    }

    std::string SinModel::json() {
        std::stringstream buffer;
        buffer << "{\"type\": \"Sin\", \"params\": [" <<
            this->a << "," << this->b <<
            "," << this->c << "," << this->d
            << "]}";
        return buffer.str();
    }

    double CosModel::call(double t) {
        return this->a * cos(this->b * t + this->c) + this->d;
    }

    std::string CosModel::json() {
        std::stringstream buffer;
        buffer << "{\"type\": \"Sin\", \"params\": [" <<
            this->a << "," << this->b <<
            "," << this->c << "," << this->d
            << "]}";
        return buffer.str();
    }


}
