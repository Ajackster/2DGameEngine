#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "Constants.h"
#include "EntityManager.h"
#include "Component.h"

class EntityManager;
class Component;

class Entity {
public:
    std::string id;
    LayerType layer;
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string id, LayerType layer);
    void Initialize();
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool IsActive() const;
    void ListAllComponents() const;

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
        T * newComponent(new T(std::forward<TArgs>(args)...));
        newComponent->entity = this;
        components.emplace_back(newComponent);
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        return *newComponent;
    }
    
    template <typename T>
    T* GetComponent() {
        return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }
    
    template <typename T>
    bool HasComponent() const {
        return componentTypeMap.find(&typeid(T)) != componentTypeMap.end();
    }
private:
    EntityManager& manager;
    bool isActive;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentTypeMap;
};

#endif
