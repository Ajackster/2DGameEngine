#include "KeyboardControl.h"

void KeyboardControl::Initialize() {
    transform = entity->GetComponent<Transform>();
    sprite = entity->GetComponent<Sprite>();
}

void KeyboardControl::Update(float deltaTime) {
    glm::vec2 newPosition = transform->GetPosition();
    glm::vec2 directionVector = glm::vec2(
        Game::inputState->GetAxis(InputState::Axis::HORIZONTAL),
        Game::inputState->GetAxis(InputState::Axis::VERTICAL)
    );

    if (directionVector.x != 0 || directionVector.y != 0) {
        glm::vec2 normalized = glm::normalize(directionVector);
        newPosition.x += normalized.x * 50 * deltaTime;
        newPosition.y += normalized.y * 50 * deltaTime;
    }

    transform->UpdatePosition(newPosition);
}
