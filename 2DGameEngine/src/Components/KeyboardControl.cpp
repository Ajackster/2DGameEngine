#include "KeyboardControl.h"

void KeyboardControl::Initialize() {
    transform = entity->GetComponent<Transform>();
    sprite = entity->GetComponent<Sprite>();
}

void KeyboardControl::Update(float deltaTime) {
    if (Game::inputManager->IsPressed("Up")) {
        if (sprite->IsPlayingAnimation("UpAnimation") == false) {
            sprite->Play("UpAnimation");
        }

        transform->velocity.y = -200;
    }
    else {
        transform->velocity.y = 0;
    }

    if (Game::inputManager->IsPressed("Right")) {
        if (sprite->IsPlayingAnimation("RightAnimation") == false) {
            sprite->Play("RightAnimation");
        }

        transform->velocity.x = 200;
    }
    else {
        transform->velocity.x = 0;
    }

    if (Game::inputManager->IsPressed("Down")) {
        if (sprite->IsPlayingAnimation("DownAnimation") == false) {
            sprite->Play("DownAnimation");
        }

        transform->velocity.y = 200;
    }
    else if (Game::inputManager->IsPressed("Up") == false) {
        transform->velocity.y = 0;
    }

    if (Game::inputManager->IsPressed("Left")) {
        if (sprite->IsPlayingAnimation("LeftAnimation") == false) {
            sprite->Play("LeftAnimation");
        }

        transform->velocity.x = -200;
    }
    else if (Game::inputManager->IsPressed("Right") == false) {
        transform->velocity.x = 0;
    }
}
