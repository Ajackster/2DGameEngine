#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "./TextureManager.h"
#include "./EntityManager.h"

class AssetManager {
public:
    AssetManager(EntityManager* entityManager);
    ~AssetManager();
    void ClearData();
    void AddTexture(std::string textureId, const char* filePath);
    SDL_Texture* GetTexture(std::string textureId);
private:
    EntityManager* entityManager;
    std::map<std::string, SDL_Texture*> textures;
};

#endif /* ASSETMANAGER_H */

