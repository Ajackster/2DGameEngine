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
    
    Tile(int sourceRectX, int sourceRectY, int x, int y, int tileWidth, int tileHeight, int tileScale, std::string textureId) {
        texture = Game::assetManager->GetTexture(textureId);
        
        sourceRect.x = sourceRectX;
        sourceRect.y = sourceRectY;
        sourceRect.w = tileWidth;
        sourceRect.h = tileHeight;
        
        destinationRect.x = x;
        destinationRect.y = y;
        destinationRect.w = tileWidth * tileScale;
        destinationRect.h = tileHeight * tileScale;
        
        position.x = x;
        position.y = y;
    }
    
    ~Tile() {
        SDL_DestroyTexture(texture);
    }
    
    void Update(float deltaTime) override {
        destinationRect.x = position.x - Game::camera.x;
        destinationRect.y = position.y - Game::camera.y;
    }
    
    void Render() override {
        TextureManager::Draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
    }
private:

};

#endif /* TILE_H */

