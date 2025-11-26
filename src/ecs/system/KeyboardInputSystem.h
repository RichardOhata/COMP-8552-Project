//
// Created by richa on 2025-09-23.
//

#ifndef TEST_KEYBOARDINPUTSYSTEM_H
#define TEST_KEYBOARDINPUTSYSTEM_H
#include <iostream>
#include <memory>
#include <vector>
#include <SDL3/SDL_events.h>

#include "Component.h"
#include "Entity.h"


class KeyboardInputSystem {
    public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, const SDL_Event& event) {
        const bool *state = SDL_GetKeyboardState(NULL);
        for (auto& e : entities) {
            if (e->hasComponent<PlayerTag>() && e->hasComponent<Velocity>()) {
                auto& v= e->getComponent<Velocity>();

                v.direction.x = 0;
                v.direction.y = 0;

                if (state[SDL_SCANCODE_W]) v.direction.y = -1;
                if (state[SDL_SCANCODE_S]) v.direction.y = 1;
                if (state[SDL_SCANCODE_A]) v.direction.x = -1;
                if (state[SDL_SCANCODE_D]) v.direction.x = 1;

                if (v.direction.x != 0 && v.direction.y != 0) {
                    v.direction.x *= 0.7071f;
                    v.direction.y *= 0.7071f;
                }

                if (e->hasComponent<ParryInput>()) {
                    auto& parry = e->getComponent<ParryInput>();
                    parry.parryPressed = state[SDL_SCANCODE_F];
                }
            }
        }
    }
};

#endif //TEST_KEYBOARDINPUTSYSTEM_H