#include "Random.hpp"

#include <random>

void rngRefreshSeed() {
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

unsigned rngU() {
    unsigned value = generator();
    return value;
}

double rngD() {
    return ((double) rngU() / (double) std::minstd_rand0::max());
}

float rngF() {
    return (float)rngD();;
}

unsigned rngRangeU(unsigned lowest, unsigned highest) {
    unsigned diff = highest - lowest;
    return rngU() % diff + lowest;
}

float rngRangeF(float lowest, float highest) {
    float diff = highest - lowest;
    return rngF() * diff + lowest;
}

double rngRangeD(double lowest, double highest) {
    double diff = highest - lowest;
    return rngD() * diff + lowest;
}
