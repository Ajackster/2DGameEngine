#include <fstream>
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Components/Tile.h"

extern EntityManager entityManager;

Map::Map(std::string textureId, int scale, int tileWidth, int tileHeight) {
    this->textureId = textureId;
    this->scale = scale;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
    // TODO: read the map tile definitions from the .map file
    std::fstream mapFile;
    mapFile.open(filePath);
    
    for (int y = 0; y < mapSizeY; y++) {
        for (int x = 0; x < mapSizeX; x++) {
            char ch;
            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * tileHeight;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tileWidth;

            AddTile(sourceRectX, sourceRectY, x, y);
            mapFile.ignore();
        }
    }

    mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y) {
    // TODO: Add a new tile entity in the game scene
    Entity& newTile(entityManager.AddEntity("Tile " + std::to_string(tileEntityIndex), LayerType::TILEMAP_LAYER));
    newTile.AddComponent<Tile>(sourceRectX, sourceRectY, x, y, tileWidth, tileHeight, scale, textureId, false);

    tileEntityIndex++;
}
