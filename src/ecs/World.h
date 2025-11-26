//
// Created by richa on 2025-09-16.
//

#ifndef TEST_WORLD_H
#define TEST_WORLD_H
#include <memory>
#include <vector>

#include "AnimationSystem.h"
#include "CollisionSystem.h"
#include "RenderSystem.h"
#include "Entity.h"
#include "EventManager.h"
#include "KeyboardInputSystem.h"
#include "MovementSystem.h"
#include "Map.h"
#include "CameraSystem.h"
#include "DestructionSystem.h"
#include "HomingSystem.h"
#include "LifetimeSystem.h"
#include "MouseInputSystem.h"
#include "SpawnTimerSystem.h"
#include "SawBladeMovementSystem.h"
#include "player_mechanics/ParrySystem.h"

class World {
    Map map;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> deferredEntities;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    KeyboardInputSystem keyboardInputSystem;
    CollisionSystem collisionSystem;
    AnimationSystem animationSystem;
    CameraSystem cameraSystem;
    EventManager eventManager;
    SpawnTimerSystem spawnTimerSystem;
    DestructionSystem destructionSystem;
    SawbladeMovementSystem sawbladeMovementSystem;
    MouseInputSystem mouseInputSystem;
    LifetimeSystem lifetimeSystem;
    HomingSystem homingSystem;
    ParrySystem parrySystem;
public:
    World();
    void update(float dt, const SDL_Event& event) {
        keyboardInputSystem.update(entities, event);
        movementSystem.update(entities, dt);
        collisionSystem.update(*this);
        animationSystem.update(entities, dt);
        cameraSystem.update(entities);
        spawnTimerSystem.update(entities, dt);
        destructionSystem.update(entities);
        sawbladeMovementSystem.update(entities, dt);
        mouseInputSystem.update(*this, event);
        lifetimeSystem.update(entities, dt);
        homingSystem.update(entities, dt, getPlayer()->getComponent<Transform>().position);
        parrySystem.update(entities, dt);
        synchronizeEntities();
        cleanup();
    }

    void render() {
        for (auto& entity : entities) {
          if (entity->hasComponent<Camera>()) {
            map.draw(entity->getComponent<Camera>());
            break;
            }
            }
        renderSystem.render(entities);
    }

    Entity& createEntity() {
        entities.emplace_back(std::make_unique<Entity>());
        return * entities.back();
    }

    Entity& createDeferredEntity() {
        deferredEntities.emplace_back(std::make_unique<Entity>());
        return *deferredEntities.back();
    }

    std::vector<std::unique_ptr<Entity>>& getEntities() {
        return entities;
    }

    void cleanup() {
        std::erase_if(
            entities,
            [](std::unique_ptr<Entity>& e) {
                return !e->isActive();
            }
            );
    }

    void synchronizeEntities() {
        if (!deferredEntities.empty()) {
            std::move(
                deferredEntities.begin(),
                deferredEntities.end(),
                std::back_inserter(entities)
                );
            deferredEntities.clear();
        }
    }

    EventManager& getEventManager() {
        return eventManager;
    }

    Map& getMap() {
        return map;
    }

    Vector2D respawnPoint{};

    void setRespawn(Vector2D respawnPoint) {
        this->respawnPoint = respawnPoint;
    }

private:
    Entity* getPlayer() const {
        for (auto& e : entities) {
            if (e->hasComponent<PlayerTag>()) {
                return e.get();
            }
        }
        return nullptr;
    }
};
#endif //TEST_WORLD_H