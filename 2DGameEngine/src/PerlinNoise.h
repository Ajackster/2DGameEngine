#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <vector>

class PerlinNoise {
std::vector<int> p;
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);
    float Noise(float x, float y, float z);
private:
    float Fade(float t);
    float Lerp(float t, float a, float b);
    float Grad(int hash, float x, float y, float z);
};

#endif
