#include "Tile.h"
#include "../Utils.h"
#include "../Game.h"

Tile::Tile(int sourceRectX, int sourceRectY, int x, int y, int tileWidth, int tileHeight, int tileScale, std::string textureId, MapLayer mapLayer) {
    this->texture = Game::assetManager->GetTexture(textureId);

    this->sourceRect.x = sourceRectX;
    this->sourceRect.y = sourceRectY;
    this->sourceRect.w = tileWidth;
    this->sourceRect.h = tileHeight;

    this->destinationRect.x = x;
    this->destinationRect.y = y;
    this->destinationRect.w = tileWidth * tileScale;
    this->destinationRect.h = tileHeight * tileScale;

    this->position.x = x;
    this->position.y = y;
    this->mapLayer = mapLayer;
}

Tile::~Tile() {
    SDL_DestroyTexture(texture);
}

void Tile::Update(float deltaTime) {
    destinationRect.x = position.x - Game::camera.x;
    destinationRect.y = position.y - Game::camera.y;
}

void Tile::Render() {
    TextureManager::Draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
}
