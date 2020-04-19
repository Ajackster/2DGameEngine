#include "Transform.h"
#include "../Utils.h"

Transform::Transform(int posX, int posY, int width, int height, int scale) {
    position = glm::vec2(posX, posY);
    this->width = width;
    this->height = height;
    this->scale = scale;
}

void Transform::UpdatePosition(glm::vec2 newPosition) {
    // TODO: Check for collisions
    position = newPosition;
}

void Transform::Initialize() {
}

void Transform::Update(float deltaTime) {
}

void Transform::Render() {
}
