#include "KeyboardControl.h"

void KeyboardControl::Initialize() {
    transform = entity->GetComponent<Transform>();
    sprite = entity->GetComponent<Sprite>();
}

void KeyboardControl::Update(float deltaTime) {
    glm::vec2 newPosition = transform->GetPosition();
    int dX = 0;
    int dY = 0;

    if (Game::inputState->IsPressed("Up")) {
        dY = -1;
    }

    if (Game::inputState->IsPressed("Right")) {
        dX = 1;
    }

    if (Game::inputState->IsPressed("Down")) {
        if (dY != 0) {
            dY = 0;
        }
        else {
            dY = 1;
        }
    }

    if (Game::inputState->IsPressed("Left")) {
        if (dX != 0) {
            dX = 0;
        }
        else {
            dX = -1;
        }
    }

    newPosition.x += dX * 50 * deltaTime;
    newPosition.y += dY * 50 * deltaTime;

    transform->UpdatePosition(newPosition);
}
