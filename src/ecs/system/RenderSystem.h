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
#include "../../manager/TextureManager.h"
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
                if (!sprite.visible) continue;
                if (sprite.renderLayer != RenderLayer::World && !entity->hasComponent<ProjectileTag>()) continue;
                // Implemented scaling for sprite
                if (sprite.originalWidth == 0) {
                    sprite.originalWidth = sprite.dst.w;
                    sprite.originalHeight = sprite.dst.h;
                }


                float scaledWidth = sprite.originalWidth * t.scale;
                float scaledHeight = sprite.originalHeight * t.scale;

                sprite.dst.x = t.position.x - cam.view.x - (scaledWidth - sprite.originalWidth) / 2;
                sprite.dst.y = t.position.y - cam.view.y - (scaledHeight - sprite.originalHeight) / 2;
                sprite.dst.w = scaledWidth;
                sprite.dst.h = scaledHeight;


                if (entity->hasComponent<Animation>()) {
                    auto& anim = entity->getComponent<Animation>();
                    sprite.src = anim.clips[anim.currentClip].frameIndicies[anim.currentFrame];
                }


                TextureManager::draw(sprite.texture, &sprite.src, &sprite.dst);

            }
        }
    }
};

#endif //TEST_RENDERSYSTEM_H