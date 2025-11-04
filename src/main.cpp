#include <iostream>

#include "Game.h"
#include <SDL3/SDL.h>

Game *game = nullptr;
int main() {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint64 ticks = SDL_GetTicks();
    int actualFrameTime;
    float deltaTime = 0.0f;
    game = new Game();
    game->init("Reflex", 1280, 720, false);


    while (game->running()) {
        Uint32 frameStart = SDL_GetTicks();
        deltaTime = static_cast<float>(frameStart - ticks) / 1000.0f;
        ticks = frameStart;
        game->handleEvents();
        game->update(deltaTime);
        game->render();

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    delete game;
    return 0;
}