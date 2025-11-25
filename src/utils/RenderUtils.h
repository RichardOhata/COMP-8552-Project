//
// Created by richa on 2025-11-24.
//

#ifndef TEST_RENDERUTILS_H
#define TEST_RENDERUTILS_H
#include <SDL3/SDL_rect.h>

class RenderUtils {
public:
    static SDL_FRect getScaledDest(const SDL_FRect& dest, float scale) {
        return SDL_FRect{
            dest.x + dest.w * (1- scale) / 2,
            dest.y + dest.h * (1 - scale) / 2,
            dest.w * scale,
            dest.h * scale
        };
    }
};
#endif //TEST_RENDERUTILS_H