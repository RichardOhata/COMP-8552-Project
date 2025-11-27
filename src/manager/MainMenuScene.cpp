//
// Created by richa on 2025-11-24.
//

#include "MainMenuScene.h"

#include "AssetManager.h"
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



    auto& title = world.createEntity();
    Label label = {
        "Reflex",
        AssetManager::getFont("Bold Pixel"),
{255, 0, 0, 255},
        LabelType::PlayerPosition,
        "Test",

    };
    label.dirty = true;
    TextureManager::loadLabel(label);
    label.dst.x = (w - label.dst.w) / 2;
    label.dst.y = h / 4 - label.dst.h / 2;
    title.addComponent<Label>(label);
    title.addComponent<Transform>(Vector2D{label.dst.x, label.dst.y}, 0.0, 1.0);
}
