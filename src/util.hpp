
#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

namespace Dodger {

    float rand_float(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }
}

#endif
