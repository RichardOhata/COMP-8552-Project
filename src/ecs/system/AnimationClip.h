//
// Created by richa on 2025-10-14.
//

#ifndef TEST_ANIMATIONCLIP_H
#define TEST_ANIMATIONCLIP_H
#include <vector>
#include <SDL3/SDL_rect.h>

struct AnimationClip {
    std::vector<SDL_FRect> frameIndicies;
};
#endif //TEST_ANIMATIONCLIP_H