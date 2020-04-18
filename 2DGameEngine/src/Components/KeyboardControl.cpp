#include "KeyboardControl.h"

void KeyboardControl::Initialize() {
    transform = entity->GetComponent<Transform>();
    sprite = entity->GetComponent<Sprite>();
}

void KeyboardControl::Update(float deltaTime) {
    glm::vec2 newPosition = transform->GetPosition();
    if (Game::inputManager->IsPressed("Up")) {
        if (sprite->IsPlayingAnimation("UpAnimation") == false) {
            sprite->Play("UpAnimation");
        }

        newPosition.y += -200 * deltaTime;
    }

    if (Game::inputManager->IsPressed("Right")) {
        if (sprite->IsPlayingAnimation("RightAnimation") == false) {
            sprite->Play("RightAnimation");
        }

        newPosition.x += 200 * deltaTime;
    }

    if (Game::inputManager->IsPressed("Down")) {
        if (sprite->IsPlayingAnimation("DownAnimation") == false) {
            sprite->Play("DownAnimation");
        }

        newPosition.y += 200 * deltaTime;
    }

    if (Game::inputManager->IsPressed("Left")) {
        if (sprite->IsPlayingAnimation("LeftAnimation") == false) {
            sprite->Play("LeftAnimation");
        }

        newPosition.x += -200 * deltaTime;
    }

    transform->UpdatePosition(newPosition);
}
