//
// Created by richa on 2025-09-29.
//

#ifndef TEST_COLLISION_H
#define TEST_COLLISION_H
#include <SDL3/SDL_rect.h>

#include "Component.h"

class Collision {
public:
    static bool AABB(const SDL_FRect& reactA, const SDL_FRect& rectB);
    static bool AABB(const Collider& colA, const Collider& colB);
};
#endif //TEST_COLLISION_H