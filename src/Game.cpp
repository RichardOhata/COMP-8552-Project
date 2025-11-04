//
// Created by richa on 2025-09-02.
//

#include "Game.h"
#include "Map.h"
#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>
#include "manager/AssetManager.h"

// #include "GameObject.h"


// GameObject *player = nullptr;
std::function<void(std::string)> Game::onSceneChangeRequest;
Game::Game() {
}


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

    sceneManager.loadScene("level1", "../asset/Level_1.tmx", width, height);
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
