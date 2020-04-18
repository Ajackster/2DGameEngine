#include "Transform.h"

Transform::Transform(int posX, int posY, int w, int h, int s) {
    position = glm::vec2(posX, posY);
    width = w;
    height = h;
    scale = s;
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
