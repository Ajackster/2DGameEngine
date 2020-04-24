#include "PlayerController.h"
#include "../Utils.h"

void PlayerController::Initialize() {
    transform = entity->GetComponent<Transform>();
    sprite = entity->GetComponent<Sprite>();
    avatar = entity->GetComponent<Avatar>();
}

void PlayerController::Update(float deltaTime) {
    glm::vec2 newPosition = transform->GetPosition();
    
    float x = Game::inputState->GetAxis(InputState::Axis::HORIZONTAL);
    float y = Game::inputState->GetAxis(InputState::Axis::VERTICAL);

    // We rotate x and y so that north -> northeast because it feels better in isometric
    float rotatedX = (x * glm::cos(glm::radians(-45.0f))) - (y * glm::sin(glm::radians(-45.0f)));
    float rotatedY = (x * glm::sin(glm::radians(-45.0f))) + (y * glm::cos(glm::radians(-45.0f)));
    glm::vec2 rotatedDirectionVector = glm::vec2(rotatedX, rotatedY);

    glm::vec2 isometricCoord = utils::CartesianToIsometric(rotatedDirectionVector);
    SetAvatarDirection(isometricCoord.x, isometricCoord.y);

    if (rotatedX != 0 || rotatedY != 0) {
        glm::vec2 normalized = glm::normalize(rotatedDirectionVector);
        newPosition.x += normalized.x * 200 * deltaTime;
        newPosition.y += normalized.y * 200 * deltaTime;
    }

    transform->UpdatePosition(newPosition);
}

void PlayerController::SetAvatarDirection(float dirX, float dirY) const {
    if (dirX > 0 && dirY < 0) {
        // Northeast
        avatar->SetAvatarState(Avatar::AvatarState::RUNNING);
        avatar->SetFacingDirection(Direction::NORTH_EAST);
        return;
    }
    else if (dirX > 0 && dirY > 0) {
        // Southeast
        avatar->SetAvatarState(Avatar::AvatarState::RUNNING);
        avatar->SetFacingDirection(Direction::SOUTH_EAST);
        return;
    }
    else if (dirX < 0 && dirY > 0) {
        // Southwest
        avatar->SetAvatarState(Avatar::AvatarState::RUNNING);
        avatar->SetFacingDirection(Direction::SOUTH_WEST);
        return;
    }
    else if (dirX < 0 && dirY < 0) {
        // NorthWest
        avatar->SetAvatarState(Avatar::AvatarState::RUNNING);
        avatar->SetFacingDirection(Direction::NORTH_WEST);
        return;
    }

    if (dirY < 0) {
        // North
        avatar->SetAvatarState(Avatar::AvatarState::RUNNING);
        avatar->SetFacingDirection(Direction::NORTH);
        return;
    }
    else if (dirX > 0) {
        // East
        avatar->SetAvatarState(Avatar::AvatarState::RUNNING);
        avatar->SetFacingDirection(Direction::EAST);
        return;
    }
    else if (dirY > 0) {
        // South
        avatar->SetAvatarState(Avatar::AvatarState::RUNNING);
        avatar->SetFacingDirection(Direction::SOUTH);
        return;
    }
    else if (dirX < 0) {
        // West
        avatar->SetAvatarState(Avatar::AvatarState::RUNNING);
        avatar->SetFacingDirection(Direction::WEST);
        return;
    }

    avatar->SetAvatarState(Avatar::AvatarState::IDLE);
}
