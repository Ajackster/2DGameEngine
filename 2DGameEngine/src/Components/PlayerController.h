#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "../Game.h"
#include "../EntityManager.h"
#include "./Transform.h"
#include "./Sprite.h"
#include "./Avatar.h"

class PlayerController: public Component {
public:
    Transform* transform;
    Sprite* sprite;
    Avatar* avatar;
        
    void Initialize() override;
    void Update(float deltaTime);
private:
    void SetAvatarDirection(float dirX, float dirY) const;
};

#endif /* PLAYERCONTROLLER_H */

