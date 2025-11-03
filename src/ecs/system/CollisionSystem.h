//
// Created by richa on 2025-09-29.
//

#ifndef TEST_COLLISIONSYSTEM_H
#define TEST_COLLISIONSYSTEM_H

#include <memory>
#include <vector>

#include "Entity.h"
#include "TextureManager.h"
class World;

class CollisionSystem {
public:
    void update(World& world);
private:
    std::vector<Entity*> queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities);
};

#endif //TEST_COLLISIONSYSTEM_H