//
// Created by richa on 2025-10-21.
//

#ifndef TEST_SCENE_H
#define TEST_SCENE_H
#include <SDL3/SDL_events.h>


#include "World.h"


class Scene {
public:
    Scene(const char* sceneName, const char* mapPath, int windowWidth, int windowHeight, bool isLevel = true);

    void update(float dt, const SDL_Event &e) {
        world.update(dt, e);
    }

    void render() {
        world.render();
    }
    World world;

    const std::string& getName() const { return name; }

    std::vector<Entity*> getEntities() {
        std::vector<Entity*> ptrs;
        for (auto& e : world.getEntities()) {
            ptrs.push_back(e.get());
        }
        return ptrs;
    }

    void respawn() {
        for (auto& e : world.getEntities()) {
            if (e->hasComponent<PlayerTag>()) {
                e->getComponent<Transform>().position=world.respawnPoint;
                break;
            }
        }

        SDL_Texture* itemTex = TextureManager::load("../asset/coin.png");
        for (auto &spawnPoint : world.getMap().itemSpawns) {
            auto& item = world.createEntity();
            auto& itemTransform = item.addComponent<Transform>(Vector2D(spawnPoint.x, spawnPoint.y), 0.0f, 1.0f);
            SDL_FRect itemSrc{0, 0, 32, 32};
            SDL_FRect itemDest {itemTransform.position.x, itemTransform.position.y, 32, 32};
            item.addComponent<Sprite>(itemTex, itemSrc, itemDest);
            auto& itemCollider = item.addComponent<Collider>("item");
            itemCollider.rect.w = itemDest.w;
            itemCollider.rect.h = itemDest.h;
            item.addComponent<Coin>();
        }
        for (auto& e : world.getEntities()) {
            if (e->hasComponent<SceneState>()) {
                e->getComponent<SceneState>().coinsCollected = 0;
                break;
            }
        }
    }
private:
    std::string name;
    void createProjectile(Vector2D pos, Vector2D dir, int speed);
    Entity& createSawblade(Vector2D pointA, Vector2D pointB, float speed, float scale, bool stationary);

    Entity &createCircularSawblade(Vector2D center, float radius, float angularSpeed, float angle, float scale, bool clockwise);
};

#endif //TEST_SCENE_H