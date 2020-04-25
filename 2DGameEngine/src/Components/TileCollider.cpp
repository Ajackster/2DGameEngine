#include "../Game.h"
#include "TileCollider.h"

bool TileCollider::CanWalk(int xPos, int yPos) const {
    Tile& tileAtPosition = Game::map->GetTileAtPosition(xPos, yPos);
    return tileAtPosition.IsWalkable();
}
