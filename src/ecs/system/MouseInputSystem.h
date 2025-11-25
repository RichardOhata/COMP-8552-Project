//
// Created by richa on 2025-11-24.
//

#ifndef TEST_MOUSEINPUTSYSTEM_H
#define TEST_MOUSEINPUTSYSTEM_H
#include <SDL3/SDL_events.h>
class World;
class MouseInputSystem {
    public:
    void update(World& world, const SDL_Event event);
};
#endif //TEST_MOUSEINPUTSYSTEM_H