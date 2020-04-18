#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <unordered_map>
#include "./Entity.h"
#include "./Component.h"
#include "Constants.h"

class EntityManager {
private:
    std::vector<Entity*> entities;
    std::unordered_map<unsigned int, std::vector<std::string>> layerTypeToEntityIdList;
    std::unordered_map<std::string, Entity*> entityIdToEntity;

public:
    void ClearData();
    void Update(float deltaTime);
    void Render();
    bool HasNoEntities();
    Entity& AddEntity(std::string entityId, LayerType layer);
    std::vector<Entity*> GetEntities() const;
    unsigned int GetEntityCount();
    void ListOutEntities();
};

#endif