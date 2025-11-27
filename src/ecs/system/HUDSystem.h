//
// Created by richa on 2025-11-26.
//

#ifndef TEST_HUDSYSTEM_H
#define TEST_HUDSYSTEM_H
#include <memory>
#include <vector>
#include <sstream>
#include "Component.h"
#include "Entity.h"
#include "Vector2D.h"
class HUDSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        Entity* playerEntity = nullptr;

        for (auto& e : entities) {
            if (e->hasComponent<PlayerTag>()) {
                playerEntity = e.get();
                break;
            }
        }

        if (playerEntity == nullptr) return;

        auto& playerTransform = playerEntity->getComponent<Transform>();
        for (auto& e : entities) {
            if (e->hasComponent<Label>()) {
                auto& label = e->getComponent<Label>();

                if (label.type == LabelType::PlayerPosition) {
                    std::stringstream ss;
                    ss << "Player position: " << playerTransform.position;
                    label.text = ss.str();
                    label.dirty = true;
                }

            }
        }
    }
};
#endif //TEST_HUDSYSTEM_H