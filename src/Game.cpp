    //
    // Created by richa on 2025-09-02.
    //

    #include "Game.h"
    #include "Map.h"
    #include <iostream>
    #include <ostream>
    #include <SDL3/SDL.h>

#include "ColliderDebugSystem.h"
#include "manager/AssetManager.h"


    std::function<void(std::string)> Game::onSceneChangeRequest;
    std::vector<std::string> levels = {"Level_1", "Level_2", "Level_3"};
    bool Game::pendingRespawn = false;
    bool Game::wantToClearRespawnFlag = false;
    bool Game::debugColliders = false;
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

        AssetManager::loadAnimation("sawblade", "../animations/saw_blade_animations.xml");

        sceneManager.loadScene("Main_Menu","../asset/Main_Menu.tmx", width, height);
        sceneManager.loadScene("Level_1", "../asset/Level_1.tmx", width, height);
        sceneManager.loadScene("Level_2", "../asset/Level_2.tmx", width, height);
        sceneManager.loadScene("Level_3", "../asset/Level_3.tmx", width, height);
        // sceneManager.loadScene("Level_4", "../asset/Level_4.tmx", width, height);
        // sceneManager.loadScene("Level_5", "../asset/Level_5.tmx", width, height);

        sceneManager.changeSceneDeferred("Main_Menu");

        onSceneChangeRequest = [this](std::string sceneName) {
            if (sceneManager.currentScene->getName() == "level5" && sceneName == "level5") {
                std::cout << "You Win!" << std::endl;
                isRunning = false;
                return;
            }

            if (sceneName == "gameover") {
                std::cout << "You Lose!" << std::endl;
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
                 std::cout << sceneManager.currentScene->getName() << std::endl;
                 int pos = std::find(levels.begin(), levels.end(), sceneManager.currentScene->getName()) - levels.begin();
                 sceneManager.changeSceneDeferred(levels[pos+1]);
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
