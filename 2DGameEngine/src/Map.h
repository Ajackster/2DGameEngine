#ifndef MAP_H
#define MAP_H

#include <string>
#include <map>
#include "./Components/Tile.h"

class Map {
public:
    Map(std::string textureId, int scale, int tileWidth, int tileHeight);
    ~Map();
    void LoadMap(std::string filePath, std::string collisionFilePath, int mapSizeX, int mapSizeY);
    void AddTile(int sourceX, int sourceY, int x, int y, MapLayer mapLayer);
    Tile& GetTileAt(int xIndex, int yIndex);

private:
    std::map<std::string, Tile*> tileIndexToTile;
    std::string textureId;
    int scale;
    int tileWidth;
    int tileHeight;
    unsigned int tileEntityIndex = 0;
};

#endif /* MAP_H */

