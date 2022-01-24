//
// Created by Martin on 2021-01-27.
//

#ifndef GAMEENGINE_NOISE_H
#define GAMEENGINE_NOISE_H

namespace noise {
    static int seed = 0;
    float GetSeedValue(int _seed);
    void SetSeed(int _seed);
    float get1D(int x);
    float get2D(float x, float y);
}

#endif //GAMEENGINE_NOISE_H
