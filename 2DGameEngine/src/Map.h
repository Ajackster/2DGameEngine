#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
public:
    Map(std::string textureId, int scale, int tileWidth, int tileHeight);
    ~Map();
    void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
    void AddTile(int sourceX, int sourceY, int x, int y);

private:
    std::string textureId;
    int scale;
    int tileWidth;
    int tileHeight;
    unsigned int tileEntityIndex = 0;
};

#endif /* MAP_H */

