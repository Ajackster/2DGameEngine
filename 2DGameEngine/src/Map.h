#ifndef MAP_H
#define MAP_H

#include <string>
#include <map>
#include "./Components/Tile.h"

class Map {
public:
    Map(std::string waterTextureId, std::string groundTextureId, int scale, int tileWidth, int tileHeight);
    ~Map();
    void LoadMap(int mapSizeX, int mapSizeY);
    void AddTile(std::string textureId, int sourceRectX, int sourceRectY, int x, int y, MapLayer mapLayer);
    Tile& GetTileAt(int xIndex, int yIndex);
    Tile& GetTileAtPosition(int xPos, int yPos);

private:
    std::map<std::string, Tile*> tileIndexToTile;
    std::string waterTextureId;
    std::string groundTextureId;
    int scale;
    int tileWidth;
    int tileHeight;
    unsigned int tileEntityIndex = 0;
};

#endif /* MAP_H */

