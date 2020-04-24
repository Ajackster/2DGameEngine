#include "Avatar.h"

Avatar::Avatar() {
    facingDirection = Direction::SOUTH_EAST;
    avatarState = AvatarState::IDLE;
}

void Avatar::SetFacingDirection(Direction direction) {
    if (this->facingDirection == direction) {
        return;
    }

    this->facingDirection = direction;
}

Direction Avatar::GetFacingDirection() {
    return facingDirection;
}

void Avatar::SetAvatarState(Avatar::AvatarState avatarState) {
    if (this->avatarState == avatarState) {
        return;
    }

    this->avatarState = avatarState;
}

Avatar::AvatarState Avatar::GetAvatarState() {
    return avatarState;
}

void Avatar::Initialize() {
    sprite = entity->GetComponent<Sprite>();

    // All avatar sprite sheets start at west and go clockwise
    // Idle animations
    sprite->AddAnimation("Idle-West", 0, 0, 4, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Idle-NorthWest", 1, 0, 4, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Idle-North", 2, 0, 4, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Idle-NorthEast", 3, 0, 4, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Idle-East", 4, 0, 4, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Idle-SouthEast", 5, 0, 4, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Idle-South", 6, 0, 4, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Idle-SouthWest", 7, 0, 4, ANIMATION_SPEED_MS);

    // Running animations
    sprite->AddAnimation("Running-West", 0, 4, 8, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Running-NorthWest", 1, 4, 8, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Running-North", 2, 4, 8, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Running-NorthEast", 3, 4, 8, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Running-East", 4, 4, 8, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Running-SouthEast", 5, 4, 8, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Running-South", 6, 4, 8, ANIMATION_SPEED_MS);
    sprite->AddAnimation("Running-SouthWest", 7, 4, 8, ANIMATION_SPEED_MS);
}

void Avatar::Update(float deltaTime) {
    switch (this->facingDirection) {
        case Direction::NORTH: {
            if (this->avatarState == Avatar::AvatarState::RUNNING) {
                sprite->Play("Running-North");
            }
            else {
                sprite->Play("Idle-North");
            }
            break;
        }
        case Direction::NORTH_EAST: {
            if (this->avatarState == Avatar::AvatarState::RUNNING) {
                sprite->Play("Running-NorthEast");
            }
            else {
                sprite->Play("Idle-NorthEast");
            }
            break;
        }
        case Direction::EAST: {
            if (this->avatarState == Avatar::AvatarState::RUNNING) {
                sprite->Play("Running-East");
            }
            else {
                sprite->Play("Idle-East");
            }
            break;
        }
        case Direction::SOUTH_EAST: {
            if (this->avatarState == Avatar::AvatarState::RUNNING) {
                sprite->Play("Running-SouthEast");
            }
            else {
                sprite->Play("Idle-SouthEast");
            }
            break;
        }
        case Direction::SOUTH: {
            if (this->avatarState == Avatar::AvatarState::RUNNING) {
                sprite->Play("Running-South");
            }
            else {
                sprite->Play("Idle-South");
            }
            break;
        }
        case Direction::SOUTH_WEST: {
            if (this->avatarState == Avatar::AvatarState::RUNNING) {
                sprite->Play("Running-SouthWest");
            }
            else {
                sprite->Play("Idle-SouthWest");
            }
            break;
        }
        case Direction::WEST: {
            if (this->avatarState == Avatar::AvatarState::RUNNING) {
                sprite->Play("Running-West");
            }
            else {
                sprite->Play("Idle-West");
            }
            break;
        }
        case Direction::NORTH_WEST: {
            if (this->avatarState == Avatar::AvatarState::RUNNING) {
                sprite->Play("Running-NorthWest");
            }
            else {
                sprite->Play("Idle-NorthWest");
            }
            break;
        }

        default: {
            break;
        }
    }
}

void Avatar::Render() {

}
