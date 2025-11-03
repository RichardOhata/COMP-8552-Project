//
// Created by richa on 2025-10-21.
//

#ifndef TEST_DESTRUCTIONSYSTEM_H
#define TEST_DESTRUCTIONSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
class DestructionSystem {
    public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {

        Entity* cameraEntity = nullptr;

        for (auto& e : entities) {
            if (e->hasComponent<Camera>()) {
                cameraEntity = e.get();
                break;
            }

        }

        if (!cameraEntity) return;
        auto& cam = cameraEntity->getComponent<Camera>();


        for (auto& e : entities) {
            if (e->hasComponent<Transform>() && e->hasComponent<ProjectileTag>()) {
                auto& t = e->getComponent<Transform>();
                if (
                    t.position.x > cam.view.x + cam.view.w || //right edge of view
                    t.position.x < cam.view.x || // left edge
                    t.position.y > cam.view.y + cam.view.h || // bottom
                    t.position.y < cam.view.y // top
                    ) {
                    e->destroy();
                }
            }
        }
    }
};

#endif //TEST_DESTRUCTIONSYSTEM_H