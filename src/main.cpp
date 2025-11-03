#include <iostream>

#include "Game.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

Game *game = nullptr;
int main() {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint64 ticks = SDL_GetTicks();
    int actualFrameTime;
    float deltaTime = 0.0f;
    game = new Game();
    game->init("8552 Tutorial Engine", 800, 600, false);

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
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}