#ifndef MAPLAYER_H
#define MAPLAYER_H

class MapLayer {
public:
    MapLayer(std::string textureId, int tileWidth, int tileHeight);
    ~Map();
    void LoadMapLayer(std::string filePath, int mapSizeX, int mapSizeY);
};

#endif
