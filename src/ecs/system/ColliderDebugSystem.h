//
// Created by richa on 2025-11-17.
//

#ifndef TEST_COLLIDERDEBUGSYSTEM_H
#define TEST_COLLIDERDEBUGSYSTEM_H
#include <vector>
#include <SDL3/SDL_render.h>

#include "Entity.h"

class ColliderDebugSystem {
public:
    static inline void DrawAllColliders(SDL_Renderer* renderer, const std::vector<Entity*>& entities) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        for (auto* entity : entities) {
            if (entity->hasComponent<Collider>()) {
                const auto& c = entity->getComponent<Collider>();
                SDL_RenderRect(renderer, &c.rect);
            }
        }


    }
};
#endif //TEST_COLLIDERDEBUGSYSTEM_H