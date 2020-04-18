#pragma once
#include "glm.hpp"

namespace utils {
    glm::vec2 IsometricToCartesian(glm::vec2 isometricPoint) {
        glm::vec2 cartesianPoint;
        cartesianPoint.x = (2 * isometricPoint.y + isometricPoint.x) / 2;
        cartesianPoint.y = (2 * isometricPoint.y - isometricPoint.x) / 2;
        return cartesianPoint;
    }

    glm::vec2 CartesianToIsometric(glm::vec2 cartesianPoint) {
        glm::vec2 isometricPoint;
        isometricPoint.x = (cartesianPoint.x - cartesianPoint.y);
        isometricPoint.y = (cartesianPoint.x + cartesianPoint.y);
        return isometricPoint;
    }
}
