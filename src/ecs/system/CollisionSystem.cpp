//
// Created by richa on 2025-09-30.
//

#include "CollisionSystem.h"

#include "Collision.h"
#include "World.h"
#include "RenderSystem.h"

void CollisionSystem::update(World &world) {
    // Get a list of entities that have colliders and transforms
    const std::vector<Entity*> collidables = queryCollidables(world.getEntities());

    for (auto entity: collidables) {
        auto& t = entity->getComponent<Transform>();
        auto& c = entity->getComponent<Collider>();
        c.rect.x = t.position.x;
        c.rect.y = t.position.y;
    }


    for (size_t i = 0; i < collidables.size(); i++) {
        // update the collider position
        auto entityA = collidables[i];

        auto& colliderA = entityA->getComponent<Collider>();


        //check for the collider collision
        //inner loop
        for (size_t j = i + 1; j < collidables.size(); j++) {
            auto& entityB = collidables[j];
            auto& colliderB = entityB->getComponent<Collider>();

            if (Collision::AABB(colliderA, colliderB)) {
                world.getEventManager().emit(CollisionEvent(entityA, entityB));
            }
        }
    }
}

std::vector<Entity*> CollisionSystem::queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities) {
    std::vector<Entity*> collidables;
    for (auto& e : entities) {
        if (e->hasComponent<Transform>() && e->hasComponent<Collider>()) {
            collidables.push_back(e.get());
        }
    }
    return collidables;
}