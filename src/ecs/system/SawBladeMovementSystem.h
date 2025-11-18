//
// Created by richa on 2025-11-17.
//

#ifndef TEST_SAWBLADEMOVEMENTSYSTEM_H
#define TEST_SAWBLADEMOVEMENTSYSTEM_H

#include <vector>
#include <memory>

#include "Component.h"
#include "Entity.h"

class SawbladeMovementSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto& e : entities) {
            if (e->hasComponent<Transform>() && e->hasComponent<SawbladePath>()) {
                auto& t = e->getComponent<Transform>();
                auto& path = e->getComponent<SawbladePath>();
                if (path.stationary) {
                    return;
                }
                Vector2D target = path.forward ? path.pointB : path.pointA;
                Vector2D dir = (target - t.position).normalize();

                t.position += dir * path.speed * dt;

                // Check if we've reached or passed the target
                if ((dir.x > 0 && t.position.x >= target.x) ||
                    (dir.x < 0 && t.position.x <= target.x) ||
                    (dir.y > 0 && t.position.y >= target.y) ||
                    (dir.y < 0 && t.position.y <= target.y)) {
                    t.position = target;
                    path.forward = !path.forward; // reverse direction
                    }
            }
        }
    }
};
#endif //TEST_SAWBLADEMOVEMENTSYSTEM_H