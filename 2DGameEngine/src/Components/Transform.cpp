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
    if (tileCollider) {
        if (!tileCollider->CanWalk(newPosition.x, newPosition.y)) {
            return;
        }
    }

    position = newPosition;
    isometricPosition = utils::CartesianToIsometric(newPosition);
}

void Transform::Initialize() {
    if (entity->HasComponent<TileCollider>()) {
        tileCollider = entity->GetComponent<TileCollider>();
    }
}

void Transform::Update(float deltaTime) {
}

void Transform::Render() {
}
