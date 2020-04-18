#ifndef KEYBOARDCONTROL_H
#define KEYBOARDCONTROL_H

#include "../Game.h"
#include "../EntityManager.h"
#include "./Transform.h"
#include "./Sprite.h"

class KeyboardControl: public Component {
    public:
        Transform* transform;
        Sprite* sprite;
        
        void Initialize() override;
        void Update(float deltaTime);
};

#endif /* KEYBOARDCONTROL_H */

