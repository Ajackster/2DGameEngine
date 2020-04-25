#ifndef TILECOLLIDER_H
#define TILECOLLIDER_H

#include "../Component.h"

class TileCollider : public Component {
public:
    bool CanWalk(int xPos, int yPos) const;
};

#endif TILECOLLIDER_H
