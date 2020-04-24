#ifndef AVATAR_H
#define AVATAR_H

#include "../Constants.h"
#include "Sprite.h"

class Avatar : public Component {
public:
    enum class AvatarState {
        IDLE,
        RUNNING
    };

    Avatar();
    void SetFacingDirection(Direction direction);
    Direction GetFacingDirection();
    void SetAvatarState(AvatarState avatarState);
    AvatarState GetAvatarState();

    void Initialize() override;
    void Update(float deltaTime);
    void Render() override;

private:
    const unsigned int ANIMATION_SPEED_MS = 90;
    Sprite* sprite;
    Direction facingDirection;
    AvatarState avatarState;
};

#endif
