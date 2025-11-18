//
// Created by richa on 2025-09-30.
//

#include "World.h"

#include "Game.h"
#include "Entity.h"

void onCollisionPrint(const CollisionEvent& collision) {
    // if (collision.entityA && collision.entityB) {
    //     std::cout << "A collision occurred between entity A and entity B" << std::endl;
    // }
}

World::World() {
    eventManager.subscribe([this](const CollisionEvent& collision) {
        Entity* sceneStateEntity = nullptr;

        for (auto& e : entities) {
            if (e->hasComponent<SceneState>()) {
                sceneStateEntity = e.get();
                break;
            }
        }

        if (!sceneStateEntity) return;
        if (collision.entityA == nullptr || collision.entityB == nullptr) return;

        if (!(collision.entityA->hasComponent<Collider>() && collision.entityB->hasComponent<Collider>())) return;

        auto& colliderA = collision.entityA->getComponent<Collider>();
        auto& colliderB = collision.entityB->getComponent<Collider>();

        Entity* player = nullptr;
        Entity* item = nullptr;
        Entity* wall = nullptr;
        Entity* projectile = nullptr;

        if (colliderA.tag == "player" && colliderB.tag == "item") {
            player = collision.entityA;
            item = collision.entityB;
        } else if (colliderA.tag == "item" && colliderB.tag == "player") {
            player = collision.entityB;
            item = collision.entityA;
        }

        if (player && item) {
            item->destroy();
            auto& sceneState = sceneStateEntity->getComponent<SceneState>();
            sceneState.coinsCollected++;

            if (sceneState.coinsCollected > 1) {
                Game::onSceneChangeRequest("level2");
            }
        }

        if (colliderA.tag == "player" && colliderB.tag == "wall") {
         player = collision.entityA;
         wall = collision.entityB;
         } else if (colliderA.tag == "wall" && colliderB.tag == "player") {
             player = collision.entityB;
             wall = collision.entityA;
         }

        if (player && wall) {
            auto& t = player->getComponent<Transform>();
            t.position = t.oldPosition;
        }

        if (colliderA.tag == "player" && colliderB.tag == "projectile") {
            player = collision.entityA;
            projectile = collision.entityB;
       } else if (colliderA.tag == "projectile" && colliderB.tag == "player") {
           player = collision.entityB;
           projectile = collision.entityA;
       }

        if (player && projectile) {
            // player->destroy();

            Game::onSceneChangeRequest("respawn");
        }
    });



    eventManager.subscribe(onCollisionPrint);
}


