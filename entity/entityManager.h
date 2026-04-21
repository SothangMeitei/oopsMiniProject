
#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "entity.h"

class EntityManager {
    private:
        std::vector<std::shared_ptr<entity>> entities;
        std::vector<std::shared_ptr<entity>> entitiesToBeAdded;

    public:
        
        void addEntity(std::shared_ptr<entity> newEntity) {
            entitiesToBeAdded.push_back(std::move(newEntity));
        }

        void updateEntities() {
    // 1. O(N) Deletion: Erases any entity where isAlive() returns false
    std::erase_if(entities, [](const std::shared_ptr<entity>& e) {
        return !e->isAlive(); 
    });

    // 2. Append new entities efficiently
    if (!entitiesToBeAdded.empty()) {
        entities.reserve(entities.size() + entitiesToBeAdded.size());
        for (auto& e : entitiesToBeAdded) {
            entities.push_back(std::move(e));
        }
        entitiesToBeAdded.clear();
    }
}
};