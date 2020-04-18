#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SDL.h>
#include "../EntityManager.h"
#include "../Game.h"
#include "../../lib/glm/glm.hpp"

class Transform : public Component {
public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;
    Transform(int posX, int posY, int velX, int velY, int w, int h, int s);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;
};

#endif
