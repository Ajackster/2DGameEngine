#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"

class Tile: public Component {
public:
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    glm::vec2 position;
    bool isCollider;
    
    Tile(int sourceRectX, int sourceRectY, int x, int y, int tileWidth, int tileHeight, int tileScale, std::string textureId, bool isColliderTile);
    ~Tile();
    void Update(float deltaTime) override;
    void Render() override;
private:

};

#endif /* TILE_H */

