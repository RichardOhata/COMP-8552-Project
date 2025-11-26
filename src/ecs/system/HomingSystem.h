//
// Created by richa on 2025-11-26.
//

#ifndef TEST_HOMINGSYSTEM_H
#define TEST_HOMINGSYSTEM_H

#include "Vector2D.h"
#include "Component.h"
class HomingSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, float dt, const Vector2D& playerPos) {
        for (auto& e : entities) {
            if (!e->hasComponent<Velocity>() || !e->hasComponent<ProjectileTag>()) continue;

            auto& projType = e->getComponent<ProjectileType>();
            if (projType.type != ProjectileType::Bullet) continue;

            auto& velocity = e->getComponent<Velocity>();
            auto& transform = e->getComponent<Transform>();
            if (!projType.preventHoming) {
                Vector2D dir = playerPos - transform.position;
                dir.normalize();
                float turnSpeed = 5.0f;
                Vector2D currentDir = velocity.direction;
                velocity.direction = currentDir.lerp(dir, turnSpeed * dt).normalize();
            }

        }
    }
};
#endif //TEST_HOMINGSYSTEM_H