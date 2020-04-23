#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "../Game.h"
#include "../EntityManager.h"
#include "./Transform.h"
#include "./Sprite.h"

class PlayerController: public Component {
    public:
        Transform* transform;
        Sprite* sprite;
        
        void Initialize() override;
        void Update(float deltaTime);
};

#endif /* PLAYERCONTROLLER_H */

