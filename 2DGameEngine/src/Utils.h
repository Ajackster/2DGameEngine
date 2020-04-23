#ifndef UTILS_H
#define UTILS_H

#include "glm.hpp"
#include "SDL.h"

namespace utils {
    glm::vec2 IsometricToCartesian(glm::vec2 isometricPoint, SDL_Rect destinationRect);
    glm::vec2 CartesianToIsometric(glm::vec2 cartesianPoint, SDL_Rect destinationRect);
}

#endif
