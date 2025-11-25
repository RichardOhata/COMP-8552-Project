//
// Created by richa on 2025-11-24.
//

#ifndef TEST_MAINMENUSCENE_H
#define TEST_MAINMENUSCENE_H

#include "Scene.h"
#include <SDL3/SDL_events.h>

class MainMenuScene : public Scene {
public:
    using Scene::Scene;

    MainMenuScene(const char* name, const char* tmxPath, int w, int h);

    void render() {
        Scene::render(); // call base render first
        // additional UI rendering here
    }
};
#endif //TEST_MAINMENUSCENE_H