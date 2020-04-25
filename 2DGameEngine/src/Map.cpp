#include <fstream>
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Utils.h"
#include "./PerlinNoise.h"
#include "./Components/Tile.h"

extern EntityManager entityManager;

Map::Map(std::string waterTextureId, std::string groundTextureId, int scale, int tileWidth, int tileHeight) {
    this->waterTextureId = waterTextureId;
    this->groundTextureId = groundTextureId;
    this->scale = scale;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
}

void Map::LoadMap(int mapSizeX, int mapSizeY) {
    PerlinNoise perlinNoise = PerlinNoise(257);

    float mapSizeYFloat = static_cast<float>(mapSizeY);
    float mapSizeXFloat = static_cast<float>(mapSizeX);
    
    for (int y = 0; y < mapSizeY; y++) {
        for (int x = 0; x < mapSizeX; x++) { 
            float i = static_cast<float>(x) / mapSizeXFloat;
            float j = static_cast<float>(y) / mapSizeYFloat;
            float n = perlinNoise.Noise(10 * i, 10 * j, 0.8);

            if (n < 0.35) {
                // Water
                int sourceRectY = 0 * tileHeight;
                int sourceRectX = 0 * tileWidth;
                AddTile(waterTextureId, sourceRectX, sourceRectY, x, y, MapLayer::WATER);
            }
            else if (n >= 0.35 && n < 0.8) {
                // Ground
                int sourceRectY = 0 * tileHeight;
                int sourceRectX = 1 * tileWidth;
                AddTile(groundTextureId, sourceRectX, sourceRectY, x, y, MapLayer::GROUND);
            }
            else {
                // Wall
                int sourceRectY = 4 * tileHeight;
                int sourceRectX = 1 * tileWidth;
                AddTile(groundTextureId, sourceRectX, sourceRectY, x, y, MapLayer::WALL);
            }
        }
    }
}

void Map::AddTile(std::string textureId, int sourceRectX, int sourceRectY, int x, int y, MapLayer mapLayer) {
    // TODO: Add a new tile entity in the game scene
    Entity& newTile(entityManager.AddEntity("Tile " + std::to_string(tileEntityIndex), LayerType::TILEMAP_LAYER));
    newTile.AddComponent<Tile>(
        sourceRectX,
        sourceRectY,
        x * scale * (tileWidth / 2),
        y * scale * tileHeight,
        tileWidth,
        tileHeight,
        scale,
        textureId,
        mapLayer
    );

    tileIndexToTile.emplace(std::to_string(x) + "," + std::to_string(y), newTile.GetComponent<Tile>());

    tileEntityIndex++;
}

Tile& Map::GetTileAt(int xIndex, int yIndex) {
    Tile& tileRef = *tileIndexToTile.at(std::to_string(xIndex) + "," + std::to_string(yIndex));
    return tileRef;
}

Tile& Map::GetTileAtPosition(int xPos, int yPos) {
    int xIndex = glm::round((xPos + (tileWidth / 2 / 2)) / (tileWidth / 2) / scale);
    int yIndex = glm::round((yPos + tileHeight) / tileHeight / scale);

    return GetTileAt(xIndex, yIndex);
}
