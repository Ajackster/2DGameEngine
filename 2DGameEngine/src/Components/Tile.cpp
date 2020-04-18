#include "Tile.h"
#include "../Utils/IsometricCartesian.h"
#include "../Game.h"

Tile::Tile(int sourceRectX, int sourceRectY, int x, int y, int tileWidth, int tileHeight, int tileScale, std::string textureId, bool isColliderTile) {
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
    isCollider = isColliderTile;
}

Tile::~Tile() {
    SDL_DestroyTexture(texture);
}

void Tile::Update(float deltaTime) {
    glm::vec2 isometricCoord = utils::CartesianToIsometric(position, destinationRect);
    destinationRect.x = isometricCoord.x - Game::camera.x;
    destinationRect.y = isometricCoord.y - Game::camera.y;
}

void Tile::Render() {
    TextureManager::Draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
}
