//
// Created by richa on 2025-11-24.
//

#include "MainMenuScene.h"
#include "Game.h"

MainMenuScene::MainMenuScene(const char* name, const char* tmxPath, int w, int h)
    : Scene(name, tmxPath, w, h, false)
{
    auto& playBtn = world.createEntity();
    playBtn.addComponent<Transform>(Vector2D{540, 500});
    playBtn.addComponent<Collider>("ui", SDL_FRect{550, 500, 200, 80});
    playBtn.addComponent<Clickable>();
    // auto& c = playBtn.getComponent<Collider>();

    playBtn.getComponent<Clickable>().onClick = []() {
        Game::onSceneChangeRequest("Level_1");
    };
}
