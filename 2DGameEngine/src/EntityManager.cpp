#include <iostream>
#include <map>
#include <typeinfo>
#include "./EntityManager.h"

void EntityManager::ClearData() {
    for (auto& entity : entities) {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities() {
    return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityId, LayerType layer) {
    Entity* entity = new Entity(*this, entityId, layer);
    entities.emplace_back(entity);
    entityIdToEntity[entityId] = entity;

    if (layerTypeToEntityIdList.count(layer)) {
        layerTypeToEntityIdList[layer].push_back(entityId);
    }
    else {
        std::vector<std::string> entityIdList;
        entityIdList.emplace_back(entityId);

        layerTypeToEntityIdList.insert({ layer, entityIdList });
    }

    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

unsigned int EntityManager::GetEntityCount() {
    return entities.size();
}

void EntityManager::Update(float deltaTime) {
    for (auto& entity : entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for (int i = 0; i < NUM_LAYERS; i++) {
        if (layerTypeToEntityIdList[i].size() == 0) {
            continue;
        }

        for (std::string entityId : layerTypeToEntityIdList[i]) {
            entityIdToEntity[entityId]->Render();
        }
    }
}

void EntityManager::ListOutEntities() {
    for (auto& entity : entities) {
        std::cout << "Entity: " + entity->id << std::endl;
        entity->ListAllComponents();
    }
}
