//
// Created by richa on 2025-11-17.
//

#ifndef TEST_SAWBLADEMOVEMENTSYSTEM_H
#define TEST_SAWBLADEMOVEMENTSYSTEM_H

#include <cmath>
#include <vector>
#include <memory>

#include "Component.h"
#include "Entity.h"

class SawbladeMovementSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto& e : entities) {
            if (!e->hasComponent<Transform>() || !e->hasComponent<SawbladePath>()) continue;
            auto& t = e->getComponent<Transform>();
            auto& path = e->getComponent<SawbladePath>();
            if (path.stationary) continue;

            switch (path.motionType) {
                case SawbladeMotionType::Linear: {
                    Vector2D target = path.forward ? path.pointB : path.pointA;
                    Vector2D dir = (target - t.position).normalize();
                    t.position += dir * path.speed * dt;

                    // Reverse direction if reached target
                    if ((dir.x > 0 && t.position.x >= target.x) ||
                        (dir.x < 0 && t.position.x <= target.x) ||
                        (dir.y > 0 && t.position.y >= target.y) ||
                        (dir.y < 0 && t.position.y <= target.y)) {
                        t.position = target;
                        path.forward = !path.forward;
                        }
                    break;
                }
                case SawbladeMotionType::Circular: {
                    path.angle += path.angularSpeed * dt;
                    if (path.angle > 2 * 3.14159265f) path.angle -= 2 * 3.14159265f;

                    t.position.x = path.center.x + path.radius * std::cos(path.angle);
                    t.position.y = path.center.y + path.radius * std::sin(path.angle);
                    break;
                }
            }
        }
    }
};
#endif //TEST_SAWBLADEMOVEMENTSYSTEM_H