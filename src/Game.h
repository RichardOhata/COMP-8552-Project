//
// Created by richa on 2025-09-02.
//

#ifndef TEST_GAME_H
#define TEST_GAME_H
#include "manager/AudioManager.h"
#include "manager/SceneManager.h"

#endif //TEST_GAME_H

#pragma once
#include <SDL3/SDL.h>
#include "World.h"
class Game {
public:
    static bool wantToClearRespawnFlag;
    static bool debugColliders;
    static bool godMode;
    Game();
    ~Game();

    void init(const char* title, int width, int height, bool fullscreen);

    void handleEvents();
    void update(float deltaTime);

    void render();

    void destroy();

    void saveGameCompleted();

    bool running() {
        return isRunning;
    }
    static bool pendingRespawn;
    SDL_Renderer* renderer = nullptr;
    AudioManager* audioManager;
    SceneManager sceneManager;
    static std::function<void(std::string)> onSceneChangeRequest;
private:
    int frameCount = 0;
    bool isRunning = false;

    SDL_Window* window = nullptr;
    SDL_Event event;

    Uint8 r,g,b,a;

    int colorIndex = 0; // which color to use
    Uint32 lastColorChangeTime = 0;
};
