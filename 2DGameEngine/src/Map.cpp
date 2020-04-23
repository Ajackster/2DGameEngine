#include <fstream>
#include "./Game.h"
#include "./Map.h"
#include "./EntityManager.h"
#include "./Utils.h"
#include "./Components/Tile.h"

extern EntityManager entityManager;

Map::Map(std::string textureId, int scale, int tileWidth, int tileHeight) {
    this->textureId = textureId;
    this->scale = scale;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
}

void Map::LoadMap(std::string filePath, std::string collisionFilePath, int mapSizeX, int mapSizeY) {
    // TODO: read the map tile definitions from the .map file
    std::fstream mapFile;
    std::fstream mapCollisionFile;
    mapFile.open(filePath);
    mapCollisionFile.open(collisionFilePath);
    
    for (int y = 0; y < mapSizeY; y++) {
        for (int x = 0; x < mapSizeX; x++) {
            char mapCh;
            mapFile.get(mapCh);
            int sourceRectY = atoi(&mapCh) * tileHeight;
            mapFile.get(mapCh);
            int sourceRectX = atoi(&mapCh) * tileWidth;

            char mapCollisionCh;
            mapCollisionFile.get(mapCollisionCh);
            MapLayer collisionType = static_cast<MapLayer>(atoi(&mapCollisionCh));

            AddTile(sourceRectX, sourceRectY, x, y, collisionType);
            mapFile.ignore();
            mapCollisionFile.ignore();
        }
    }

    mapFile.close();
    mapCollisionFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y, MapLayer mapLayer) {
    // TODO: Add a new tile entity in the game scene
    Entity& newTile(entityManager.AddEntity("Tile " + std::to_string(tileEntityIndex), LayerType::TILEMAP_LAYER));
    newTile.AddComponent<Tile>(
        sourceRectX,
        sourceRectY,
        x * scale * 32,
        y * scale * 32,
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
