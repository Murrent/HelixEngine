#include "Random.hpp"

#include <random>

unsigned int rngRefreshSeed() {
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    return seed;
}

void rngSetSeed(unsigned int _seed) {
    generator.seed(_seed);
}

unsigned rngU() {
    unsigned value = generator();
    return value;
}

double rngD() {
    return ((double) rngU());
}

double rngD01() {
    return ((double) rngU() / (double) std::minstd_rand0::max());
}

float rngF() {
    return (float) rngU();
}

float rngF01() {
    return (float) rngD01();;
}

unsigned rngRangeU(unsigned lowest, unsigned highest) {
    unsigned diff = highest - lowest;
    return rngU() % diff + lowest;
}

float rngRangeF(float lowest, float highest) {
    float diff = highest - lowest;
    return rngF01() * diff + lowest;
}

double rngRangeD(double lowest, double highest) {
    double diff = highest - lowest;
    return rngD01() * diff + lowest;
}
