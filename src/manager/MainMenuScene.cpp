//
// Created by richa on 2025-11-24.
//

#include "MainMenuScene.h"
#include "Game.h"

MainMenuScene::MainMenuScene(const char* name, const char* tmxPath, int w, int h)
    : Scene(name, tmxPath, w, h, false)
{
    auto& playBtn = world.createEntity();
    playBtn.addComponent<Transform>(Vector2D{300, 300});
    playBtn.addComponent<Collider>("ui", SDL_FRect{300, 300, 200, 60});
    playBtn.addComponent<Clickable>();
    // auto& c = playBtn.getComponent<Collider>();
    // c.rect.x = playBtn.getComponent<Transform>().position.x;
    // c.rect.y = playBtn.getComponent<Transform>().position.y;
    // c.rect.w = 200;
    // c.rect.h = 60;
    auto& c = playBtn.getComponent<Collider>();

    playBtn.getComponent<Clickable>().onClick = []() {
        std::cout << "PLAY clicked!" << std::endl;
        Game::onSceneChangeRequest("Level_1");
    };
}
