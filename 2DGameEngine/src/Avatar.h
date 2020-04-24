#ifndef AVATAR_H
#define AVATAR_H

#include "../Game.h"
#include "../EntityManager.h"
#include "./Components/Sprite.h"

class Avatar: public Component {
public:

private:
    Sprite* sprite;
};

#endif
