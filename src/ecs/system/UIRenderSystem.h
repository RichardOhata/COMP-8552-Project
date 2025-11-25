//
// Created by richa on 2025-11-24.
//

#ifndef TEST_UIRENDERSYSTEM_H
#define TEST_UIRENDERSYSTEM_H
#include <memory>
#include <vector>

#include "Component.h"
#include "RenderUtils.h"

class UIRenderSystem {
    public:
    void render(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& e : entities) {
            if (e->hasComponent<Transform>() && e->hasComponent<Sprite>()) {
                auto transform = e->getComponent<Transform>();
                auto sprite = e->getComponent<Sprite>();

                if (sprite.renderLayer != RenderLayer::UI) continue;

                sprite.dst.x = transform.position.x;
                sprite.dst.y = transform.position.y;

                if (sprite.visible) {
                    SDL_FRect scaledDest = RenderUtils::getScaledDestRect(sprite.dst, transform.scale);
                    TextureManager::draw(sprite.texture, sprite.src, scaledDest);
                }

            }
        }
    }
};
#endif //TEST_UIRENDERSYSTEM_H