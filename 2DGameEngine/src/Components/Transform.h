#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SDL.h>
#include "../EntityManager.h"
#include "../Game.h"
#include "../../lib/glm/glm.hpp"

class Transform : public Component {
public:
    glm::vec2 GetPosition() const { return position; };
    void UpdatePosition(glm::vec2 newPosition);
    int width;
    int height;
    int scale;
    Transform(int posX, int posY, int w, int h, int s);
    void Initialize() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    glm::vec2 position;
    glm::vec2 isometricPosition;
};

#endif
