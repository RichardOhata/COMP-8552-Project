//
// Created by richa on 2025-10-21.
//

#ifndef TEST_SCENEMANAGER_H
#define TEST_SCENEMANAGER_H
#include <memory>
#include <unordered_map>

#include "MainMenuScene.h"
#include "Scene.h"

struct SceneParams {
    const char* name;
    const char* mapPath;
    int windowWidth;
    int windowHeight;
    bool isLevel;
};

class SceneManager {

    std::unordered_map<std::string, SceneParams> sceneParam;
    std::string pendingScene;

    void changeScene(const std::string& name) {
        auto it = sceneParam.find(name);
        if (it != sceneParam.end()) {
            const auto& params = it->second;
            if (name == "Main_Menu") {
                // Create MainMenuScene instead of Scene
                currentScene = std::make_unique<MainMenuScene>(
                    params.name, params.mapPath, params.windowWidth, params.windowHeight
                );
            } else {
                currentScene = std::make_unique<Scene>(
                    params.name, params.mapPath, params.windowWidth, params.windowHeight, params.isLevel
                );
            }
        }
        else {
            std::cerr << "Scene " << name << " not found!" << std::endl;
        }
    }

public:
    std::unique_ptr<Scene> currentScene;
    void loadScene(const char* sceneName, const char* mapPath, int windowWidth, int windowHeight, bool isLevel = true) {
        sceneParam[sceneName] = {sceneName, mapPath, windowWidth, windowHeight, isLevel};
    }

    void changeSceneDeferred(const std::string& name) {
        pendingScene = name;
    }

    void update(const float dt, const SDL_Event &e) {
        if (currentScene) currentScene->update(dt, e);
        if (!pendingScene.empty()) {
            changeScene(pendingScene);
            pendingScene.clear();
        }
    }

    void render() const {
       if (currentScene) currentScene->render();
    }

    void respawn() const {
        currentScene->respawn();
    }
};

#endif //TEST_SCENEMANAGER_H