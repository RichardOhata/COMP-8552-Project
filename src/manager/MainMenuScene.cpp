//
// Created by richa on 2025-11-24.
//

#include "MainMenuScene.h"

#include <fstream>

#include "AssetManager.h"
#include "Game.h"
#include "json.hpp"
#include "JsonLoader.h"

MainMenuScene::MainMenuScene(const char* name, const char* tmxPath, int w, int h)
    : Scene(name, tmxPath, w, h, false)
{
    auto& playBtn = world.createEntity();
    playBtn.addComponent<Transform>(Vector2D{(w - 160) / 2.0f -2.5f, 450}, 0.0f, 1.4f); // raised Y
    playBtn.addComponent<Collider>("ui", SDL_FRect{(w - 160) / 2.0f, 450, 160, 80});
    playBtn.addComponent<Clickable>();
    playBtn.getComponent<Clickable>().onClick = []() {
        Game::onSceneChangeRequest("Level_1");
    };
    SDL_Texture* uiTex = TextureManager::load("../asset/sprites/start_btn.png");
    SDL_FRect src {
        1,
        0,
        65,
        34
    };
    SDL_FRect dest {
        (w - 160) / 2.0f - 2.5f,
        450,
        160,
        80
    };
    playBtn.addComponent<Sprite>(uiTex, src, dest);


    // Quit Button
    auto& quitBtn = world.createEntity();
    quitBtn.addComponent<Transform>(Vector2D{(w - 160) / 2.0f + 2.5f, 570}, 0.0f, 1.0f); // raised Y
    quitBtn.addComponent<Collider>("ui", SDL_FRect{(w - 160) / 2.0f, 570, 160, 80});
    quitBtn.addComponent<Clickable>();
    quitBtn.getComponent<Clickable>().onClick = []() {
        Game::onSceneChangeRequest("quit");
    };
    SDL_Texture* uiTex_quit = TextureManager::load("../asset/sprites/quit_btn.png");
    SDL_FRect quit_src {
        0,
        0,
        61,
        34
    };
    SDL_FRect quit_dest {
        (w - 160) / 2.0f + 2.5f,
        570,
        160,
        80
    };
    quitBtn.addComponent<Sprite>(uiTex_quit, quit_src, quit_dest);

    auto& howToBtn = world.createEntity();

    // Padding from the top-right corner
    float paddingX = 40.0f;
    float paddingY = 40.0f;

    // Button size
    float btnWidth = 60.0f;
    float btnHeight = 60.0f;

    // Position (top-right with padding)
    float x_howTo = w - btnWidth - paddingX;
    float y_howTo = paddingY;

    howToBtn.addComponent<Transform>(Vector2D{x_howTo, y_howTo}, 0.0f, 1.0f);
    howToBtn.addComponent<Collider>("ui", SDL_FRect{x_howTo, y_howTo, btnWidth, btnHeight});
    howToBtn.addComponent<Clickable>();

    howToBtn.getComponent<Clickable>().onClick = []() {
        Game::onSceneChangeRequest("HowToPlay"); // Change to the HowToPlay scene
    };

    // Load texture for the button
    SDL_Texture* howToTex = TextureManager::load("../asset/sprites/how_to_play_btn.png");

    // Source rect from sprite sheet
    SDL_FRect howTo_src {
        0,    // x in sprite sheet
        0,    // y in sprite sheet
        30,   // width of sprite
        30    // height of sprite
    };

    // Destination rect (scaled to button size)
    SDL_FRect howTo_dest {
        x_howTo,
        y_howTo,
        btnWidth,
        btnHeight
    };

    howToBtn.addComponent<Sprite>(howToTex, howTo_src, howTo_dest);

    if (JsonLoader::isGameCompleted()) {
        auto& completionStar = world.createEntity();

        // Padding from the top-left corner
        float star_paddingX = 40.0f;
        float star_paddingY = 40.0f;

        // Button size
        float star_width = 60.0f;
        float star_height = 60.0f;

        // Position (top-left with padding)
        float x_star = star_paddingX;
        float y_star = star_paddingY;

        completionStar.addComponent<Transform>(Vector2D{x_star, y_star}, 0.0f, 0.75f);
        completionStar.addComponent<Collider>("ui", SDL_FRect{x_star, y_star, star_width, star_height});

        SDL_Texture* starTex = TextureManager::load("../asset/sprites/star.png");

        SDL_FRect star_src {
            0, 0, 25, 25
        };

        SDL_FRect star_dest {
            x_star, y_star, star_width, star_height
        };

        completionStar.addComponent<Sprite>(starTex, star_src, star_dest);
    }

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
    float titleX = w / 2.0f - 300 / 2.0f - 20;
    float titleY = h / 4.0f - 65 / 2.0f;
    title.addComponent<Label>(label);
    title.addComponent<Transform>(Vector2D{titleX, titleY}, 0.0, 1.0);}


// Move into own system later
bool MainMenuScene::isGameCompleted() {
    std::ifstream file("save.json");
    if (!file.is_open()) return false;

    nlohmann::json j;
    try {
        file >> j;
    } catch (...) {
        return false; // JSON corrupted
    }

    return j.value("gameCompleted", false); // default false
}