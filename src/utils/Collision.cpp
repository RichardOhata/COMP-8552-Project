//
// Created by richa on 2025-09-29.
//

#include "Collision.h"
#include "../manager/TextureManager.h"
bool Collision::AABB(const SDL_FRect& rectA, const SDL_FRect& rectB) {

    // Check if right edge of rectA >= to left edge of rectB
    // Check if right edge of rectB >= left edge of rectA
    // Chcek if bottom edge of rectA >= top edge of rectB
    // Check if bottom edge of rectB >= top edge of rectA
    if (
        rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y) {
        return true;
    }

    return false;
}

bool Collision::AABB(const Collider& colA, const Collider& colB) {
    if (AABB(colA.rect, colB.rect)) {
        return true;
    }
    return false;
}