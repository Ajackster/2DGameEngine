#ifndef ISOMETRICCARTESIAN_H
#define ISOMETRICCARTESIAN_H

#include "glm.hpp"
#include "SDL.h"

namespace utils {
    glm::vec2 IsometricToCartesian(glm::vec2 isometricPoint, SDL_Rect destinationRect) {
        return glm::vec2(
            (isometricPoint.x / (destinationRect.w / 2) + isometricPoint.y / (destinationRect.h / 2)) / 2,
            (isometricPoint.y / (destinationRect.h / 2) - isometricPoint.x / (destinationRect.w / 2)) / 2
        );
    }

    glm::vec2 CartesianToIsometric(glm::vec2 cartesianPoint, SDL_Rect destinationRect) {
        return glm::vec2(
            (cartesianPoint.x - cartesianPoint.y) * (destinationRect.w / 2),
            (cartesianPoint.x + cartesianPoint.y) * (destinationRect.h / 2)
        );
    }
}

#endif
