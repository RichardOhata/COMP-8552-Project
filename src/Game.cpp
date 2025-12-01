    //
    // Created by richa on 2025-09-02.
    //

    #include "Game.h"

#include <filesystem>
#include <fstream>

#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>

#include "ColliderDebugSystem.h"
#include "json.hpp"
#include "JsonLoader.h"
#include "config/Config.h"
#include "manager/AssetManager.h"
#include "manager/AudioManager.h"


    std::function<void(std::string)> Game::onSceneChangeRequest;
    std::vector<std::string> levels = {"Level_1", "Level_2", "Level_3", "Level_4", "Level_5"};
    bool Game::pendingRespawn = false;
    bool Game::wantToClearRespawnFlag = false;
    bool Game::debugColliders = false;
    bool Game::godMode = false;
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

        if (TTF_Init() != 1) {
            std::cout << "TTF_Init() failed." << std::endl;
        }

        // Load fonts
        AssetManager::loadFont("Bold Pixel", Config::LOCAL_BUILD ? "../asset/font/BoldPixels.ttf" : "asset/font/BoldPixels.ttf", 130);
        AssetManager::loadFont("Arial", Config::LOCAL_BUILD ? "../asset/font/arial.ttf" : "asset/font/arial.ttf", 25);

        // Load animations
        AssetManager::loadAnimation("sawblade", Config::LOCAL_BUILD ? "../animations/saw_blade_animations.xml" : "animations/saw_blade_animations.xml");

        // Load levels
        sceneManager.loadScene("Main_Menu", Config::LOCAL_BUILD ? "../asset/levels/Main_Menu.tmx" : "asset/levels/Main_Menu.tmx", width, height);
        sceneManager.loadScene("Level_1", Config::LOCAL_BUILD ? "../asset/levels/Level_1.tmx" : "asset/levels/Level_1.tmx", width, height);
        sceneManager.loadScene("Level_2", Config::LOCAL_BUILD ? "../asset/levels/Level_2.tmx" : "asset/levels/Level_2.tmx", width, height);
        sceneManager.loadScene("Level_3", Config::LOCAL_BUILD ? "../asset/levels/Level_3.tmx" : "asset/levels/Level_3.tmx", width, height);
        sceneManager.loadScene("Level_4", Config::LOCAL_BUILD ? "../asset/levels/Level_4.tmx" : "asset/levels/Level_4.tmx", width, height);
        sceneManager.loadScene("Level_5", Config::LOCAL_BUILD ? "../asset/levels/Level_5.tmx" : "asset/levels/Level_5.tmx", width, height);

        // Audio
        audioManager = new AudioManager();
        audioManager->loadAudio("bgm", Config::LOCAL_BUILD ? "../asset/audio/kk_battle31_loop.ogg" : "asset/audio/kk_battle31_loop.ogg");
        audioManager->playMusic("bgm");

        sceneManager.changeSceneDeferred("Main_Menu");

        onSceneChangeRequest = [this](std::string sceneName) {
            if (sceneManager.currentScene->getName() == "level5" && sceneName == "level5") {
                std::cout << "You Win!" << std::endl;
                isRunning = false;
                return;
            }

            if (sceneName == "quit") {
                isRunning = false;
                return;
            }

            // Respawns in the same current scene
            if (sceneName == "respawn") {
                std::cout << "You Died!" << std::endl;
                sceneManager.currentScene->respawn();
                wantToClearRespawnFlag = true;
                return;
            }
             if (sceneName == "nextlevel") {
                 auto it = std::find(levels.begin(), levels.end(), sceneManager.currentScene->getName());
                 if (it != levels.end()) {
                     int pos = it - levels.begin();
                     if (pos + 1 < levels.size()) {
                         sceneManager.changeSceneDeferred(levels[pos + 1]);
                     } else {
                         JsonLoader::setGameCompleted(true);
                         sceneManager.changeSceneDeferred("Main_Menu");
                     }
                 } else {
                     std::cerr << "Current scene is not in levels list!" << std::endl;
                 }
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
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_C) {
                    debugColliders = !debugColliders;
                    std::cout << "Collider Debug: "
                              << (debugColliders ? "ON" : "OFF") << std::endl;
                }
                if (event.key.key == SDLK_ESCAPE) {
                    if (sceneManager.currentScene->getName() != "Main_Menu")
                    onSceneChangeRequest("Main_Menu");
                }
                if (event.key.key == SDLK_L) {
                    godMode = !godMode;
                    std::cout << "Debug Mode: "
                              << (godMode ? "ENABLED" : "DISABLED") << "\n";
                }
                break;
                default:
                break;
        }
    }

    void Game::update(float dt) {
        sceneManager.update(dt, event);
        if (wantToClearRespawnFlag) {
            pendingRespawn = false;
            wantToClearRespawnFlag = false;
        }
    }



    void Game::render() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        sceneManager.render();
        if (debugColliders) {
            ColliderDebugSystem::DrawAllColliders(renderer, sceneManager.currentScene->getEntities());
        }
        SDL_RenderPresent(renderer);

    }

    void Game::destroy() {
        TextureManager::clean();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        std::cout << "GameDestroyed" << std::endl;
    }

