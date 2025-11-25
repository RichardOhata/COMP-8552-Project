//
// Created by richa on 2025-11-24.
//


#include "MouseInputSystem.h"

#include "World.h"

void MouseInputSystem::update(World& world, const SDL_Event event) {
    float mx, my;
    SDL_GetMouseState(&mx, &my);

    for (auto& e : world.getEntities()) {
        if (!e->hasComponent<Clickable>() || !e->hasComponent<Collider>())
            continue;

        auto& clickable = e->getComponent<Clickable>();
        auto& col = e->getComponent<Collider>();

        bool inside =
            mx >= col.rect.x &&
            mx <= col.rect.x + col.rect.w &&
            my >= col.rect.y &&
            my <= col.rect.y + col.rect.h;

        // Reset one-frame state
        clickable.clicked = false;

        switch (event.type) {

            case SDL_EVENT_MOUSE_MOTION:
                clickable.hovered = inside;
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event.button.button == SDL_BUTTON_LEFT && inside) {
                    clickable.pressed = true;
                }
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event.button.button == SDL_BUTTON_LEFT) {


                    if (inside && clickable.pressed) {
                        clickable.clicked = true;

                        if (clickable.onClick)
                            clickable.onClick();
                    }

                    clickable.pressed = false;
                }
                break;
        }
    }
}
