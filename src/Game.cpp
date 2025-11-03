//
// Created by richa on 2025-09-02.
//

#include "Game.h"
#include "Map.h"
#include <iostream>
#include <ostream>

#include "manager/AssetManager.h"

// #include "GameObject.h"


// GameObject *player = nullptr;
std::function<void(std::string)> Game::onSceneChangeRequest;
Game::Game() {}

Game::~Game() {
    destroy();
}

void Game::init(const char *title, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) == 1) {
        std::cout << "Subsystem initalized..." << std::endl;
        window = SDL_CreateWindow(title, width, height, flags);
        if (window) {
            std::cout << "Window created... " << std::endl;
        }

        renderer = SDL_CreateRenderer(window, nullptr);

        if (renderer) {
            std::cout << "Renderer created... " << std::endl;
        } else {
            std::cout << "Renderer could not be created." << std::endl;
            return;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }

    // AssetManager::loadAnimation("player", "../animations/bull_animations.xml");
    AssetManager::loadAnimation("player", "../animations/cat_animations.xml");
    AssetManager::loadAnimation("enemy", "../animations/bird_animations.xml");

    sceneManager.loadScene("level1", "../asset/map.tmx", width, height);
    sceneManager.loadScene("level2", "../asset/map2.tmx", width, height);

    sceneManager.changeSceneDeferred("level1");

    onSceneChangeRequest = [this](std::string sceneName) {
        if (sceneManager.currentScene->getName() == "level2" && sceneName == "level2") {
            std::cout << "You Win!" << std::endl;
            isRunning = false;
            return;
        }

        if (sceneName == "gameover") {
            std::cout << "You Lose!" << std::endl;
            isRunning = false;
            return;
        }

        sceneManager.changeSceneDeferred(sceneName);
    };
}

void Game::handleEvents() {

    // SDL_Event event;
    SDL_PollEvent(&event);


    switch (event.type) {
        case SDL_EVENT_QUIT:
            isRunning = false;
            break;
            default:
            break;
    }
}

void Game::update(float dt) {
    sceneManager.update(dt, event);
    // Uint32 currentTime = SDL_GetTicks();
    // if (currentTime - lastColorChangeTime >= 1000) { // 1 second passed
    //     colorIndex = (colorIndex + 1) % 3; // cycle 0,1,2
    //     lastColorChangeTime = currentTime;
    // }
    //
    // // Set RGB based on colorIndex
    // switch(colorIndex) {
    //     case 0: r = 255; g = 0;   b = 0;   break; // red
    //     case 1: r = 0;   g = 255; b = 0;   break; // green
    //     case 2: r = 0;   g = 0;   b = 255; break; // blue
    // }frameCount++;
    // std::cout << frameCount << std::endl;

    // player->update(deltaTime);


}



void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    // player->draw();
    sceneManager.render();
    SDL_RenderPresent(renderer);

}

void Game::destroy() {
    TextureManager::clean();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "GameDestroyed" << std::endl;
}
