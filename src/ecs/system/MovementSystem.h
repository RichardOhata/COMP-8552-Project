//
// Created by richa on 2025-09-16.
//

#ifndef TEST_MOVEMENTSYSTEM_H
#define TEST_MOVEMENTSYSTEM_H
#include <iostream>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
class MovementSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Velocity>()) {
                auto& t = entity->getComponent<Transform>();
                auto& v  = entity->getComponent<Velocity>();

                t.oldPosition = t.position;
                Vector2D directionVec = v.direction;

                directionVec.normalize();
                Vector2D velocityVector = directionVec * v.speed;

                t.position += (velocityVector * dt);
            }

        }
    }
};
#endif //TEST_MOVEMENTSYSTEM_H