#pragma once

#include <random>
#include <chrono>

static unsigned seed = 0;
static std::minstd_rand0 generator(std::chrono::system_clock::now().time_since_epoch().count());

void rngRefreshSeed();

unsigned rngUInt();

double rngD();

float rngF();

unsigned rngRangeU(unsigned lowest, unsigned highest);

float rngRangeF(float lowest, float highest);

double rngRangeD(double lowest, double highest);
