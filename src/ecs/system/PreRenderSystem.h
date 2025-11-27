//
// Created by richa on 2025-11-27.
//

#ifndef TEST_PRERENDERSYSTEM_H
#define TEST_PRERENDERSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "TextureManager.h"


class PreRenderSystem {

public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& e : entities) {
            if (e->hasComponent<Label>() && e->getComponent<Label>().dirty) {
                TextureManager::updateLabel(e->getComponent<Label>());
            }
        }
    }
};


#endif //TEST_PRERENDERSYSTEM_H