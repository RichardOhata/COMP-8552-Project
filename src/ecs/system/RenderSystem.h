//
// Created by richa on 2025-09-16.
//

#ifndef TEST_RENDERSYSTEM_H
#define TEST_RENDERSYSTEM_H
#include <iostream>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"
#include "TextureManager.h"
class RenderSystem {
    public:
    void render(std::vector<std::unique_ptr<Entity>>& entities) {

        Entity* cameraEntity = nullptr;
        for (auto& e : entities) {
        if (e->hasComponent<Camera>()) {
            cameraEntity = e.get();
            break;
        }
}
    if (!cameraEntity) return;
    auto& cam = cameraEntity->getComponent<Camera>();
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {

                auto& t = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();
                sprite.dst.x = t.position.x - cam.view.x;
                sprite.dst.y = t.position.y - cam.view.y;

                if (entity->hasComponent<Animation>()) {
                    auto& anim = entity->getComponent<Animation>();
                    sprite.src = anim.clips[anim.currentClip].frameIndicies[anim.currentFrame];
                }

                TextureManager::draw(sprite.texture, sprite.src, sprite.dst);

            }
        }
    }
};

#endif //TEST_RENDERSYSTEM_H