//
// Created by richa on 2025-11-26.
//

#ifndef TEST_PARRYSYSTEM_H
#define TEST_PARRYSYSTEM_H
#include "vector"
#include "Component.h"

class ParrySystem {
    SDL_Texture* normalTex = TextureManager::load("../asset/Fine.svg");
    SDL_Texture* parryCooldownTex = TextureManager::load("../asset/Mad.svg");
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto& player : entities) {
            if (!player->hasComponent<PlayerTag>() || !player->hasComponent<ParryInput>() || !player->hasComponent<Transform>())
                continue;

            auto& parry = player->getComponent<ParryInput>();
            auto& playerTransform = player->getComponent<Transform>();

            // Update parry timer
            if (parry.timer > 0.0f) {
                parry.timer -= dt;
                parry.onCooldown = true;
            } else {
                parry.onCooldown = false;
            }
            if (player->hasComponent<Sprite>()) {
                auto& sprite = player->getComponent<Sprite>();
                if (parry.onCooldown) {
                    sprite.texture = parryCooldownTex;
                } else {
                   sprite.texture = normalTex;
                }
            }
            if (!parry.parryPressed || parry.onCooldown)
                continue;


            parry.timer = parry.cooldown;

            Vector2D playerPos = playerTransform.position;

            for (auto& e : entities) {
                if (!e->hasComponent<ProjectileTag>() || !e->hasComponent<ProjectileType>() || !e->hasComponent<Transform>())
                    continue;

                auto& projType = e->getComponent<ProjectileType>();
                if (projType.type != ProjectileType::Bullet) continue;

                auto& bulletTransform = e->getComponent<Transform>();
                Vector2D dirToBullet = bulletTransform.position - playerPos;
                float distance = dirToBullet.length();
                if (distance <= parry.parryRange) {
                    // Reflect bullet
                    e->getComponent<Velocity>().direction *= -1;
                    projType.preventHoming = true;
                }
            }

            parry.parryPressed = false;
        }
    }
};
#endif //TEST_PARRYSYSTEM_H