#pragma once

#include <random>
#include <chrono>

static std::minstd_rand0 generator(std::chrono::system_clock::now().time_since_epoch().count());

unsigned int rngRefreshSeed();

void rngSetSeed(unsigned int _seed);

unsigned rngUInt();

double rngD();

double rngD01();

float rngF();

float rngF01();

unsigned rngRangeU(unsigned lowest, unsigned highest);

float rngRangeF(float lowest, float highest);

double rngRangeD(double lowest, double highest);
