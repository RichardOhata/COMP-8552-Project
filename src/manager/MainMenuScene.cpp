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
    setupButtons(w, h);
    setupCompletionStar();
    setupTitle(w, h);
    setupHowToPanel(w, h);
}

// ========================
// BUTTONS SETUP
// ========================
void MainMenuScene::setupButtons(int w, int h) {

    // --- Play Button ---
    auto& playBtn = world.createEntity();
    float playX = (w - 160) / 2.0f - 2.5f;
    float playY = 450;
    playBtn.addComponent<Transform>(Vector2D{playX, playY}, 0.0f, 1.4f);
    playBtn.addComponent<Collider>("ui", SDL_FRect{(w - 160) / 2.0f, playY, 160, 80});
    playBtn.addComponent<Clickable>();
    playBtn.getComponent<Clickable>().onClick = []() {
        Game::onSceneChangeRequest("Level_1");
    };
    SDL_Texture* playTex = TextureManager::load("../asset/sprites/start_btn.png");
    SDL_FRect playSrc { 1, 0, 65, 34 };
    SDL_FRect playDest { playX, playY, 160, 80 };
    playBtn.addComponent<Sprite>(playTex, playSrc, playDest);

    // --- Quit Button ---
    auto& quitBtn = world.createEntity();
    float quitX = (w - 160) / 2.0f + 2.5f;
    float quitY = 570;
    quitBtn.addComponent<Transform>(Vector2D{quitX, quitY}, 0.0f, 1.0f);
    quitBtn.addComponent<Collider>("ui", SDL_FRect{(w - 160) / 2.0f, quitY, 160, 80});
    quitBtn.addComponent<Clickable>();
    quitBtn.getComponent<Clickable>().onClick = []() {
        Game::onSceneChangeRequest("quit");
    };
    SDL_Texture* quitTex = TextureManager::load("../asset/sprites/quit_btn.png");
    SDL_FRect quitSrc { 0, 0, 61, 34 };
    SDL_FRect quitDest { quitX, quitY, 160, 80 };
    quitBtn.addComponent<Sprite>(quitTex, quitSrc, quitDest);

    // --- How To Play Button ---
    auto& howToBtn = world.createEntity();
    float paddingX = 40.0f;
    float paddingY = 40.0f;
    float btnWidth = 60.0f;
    float btnHeight = 60.0f;
    float x_howTo = w - btnWidth - paddingX;
    float y_howTo = paddingY;
    howToBtn.addComponent<Transform>(Vector2D{x_howTo, y_howTo}, 0.0f, 1.0f);
    howToBtn.addComponent<Collider>("ui", SDL_FRect{x_howTo, y_howTo, btnWidth, btnHeight});
    howToBtn.addComponent<Clickable>();
    howToBtn.getComponent<Clickable>().onClick = [this]() {
        howToVisible = !howToVisible;

        // Toggle panel
        howToPanel->getComponent<Sprite>().visible = howToVisible;

        // Hide main title
        titleEntity->getComponent<Label>().visible = !howToVisible;

        // Toggle all panel labels
        for (auto* e : howToTextEntities) {
            if (e->hasComponent<ProjectileType>()) {
                e->getComponent<Sprite>().visible = howToVisible;
            } else {
                e->getComponent<Label>().visible = howToVisible;
            }

        }

    };
    SDL_Texture* howToTex = TextureManager::load("../asset/sprites/how_to_play_btn.png");
    SDL_FRect howToSrc {0, 0, 30, 30};
    SDL_FRect howToDest {x_howTo, y_howTo, btnWidth, btnHeight};
    howToBtn.addComponent<Sprite>(howToTex, howToSrc, howToDest);
}

// ========================
// COMPLETION STAR
// ========================
void MainMenuScene::setupCompletionStar() {
    if (!JsonLoader::isGameCompleted()) return;

    auto& star = world.createEntity();
    float starPaddingX = 40.0f;
    float starPaddingY = 40.0f;
    float starWidth = 60.0f;
    float starHeight = 60.0f;

    star.addComponent<Transform>(Vector2D{starPaddingX, starPaddingY}, 0.0f, 0.75f);
    star.addComponent<Collider>("ui", SDL_FRect{starPaddingX, starPaddingY, starWidth, starHeight});

    SDL_Texture* starTex = TextureManager::load("../asset/sprites/star.png");
    SDL_FRect starSrc { 0, 0, 25, 25 };
    SDL_FRect starDest { starPaddingX, starPaddingY, starWidth, starHeight };
    star.addComponent<Sprite>(starTex, starSrc, starDest);
}

// ========================
// TITLE SETUP
// ========================
void MainMenuScene::setupTitle(int w, int h) {
    auto& title = world.createEntity();
    Label label {
        "Reflex",
        AssetManager::getFont("Bold Pixel"),
        {255, 0, 0, 255},
        LabelType::PlayerPosition,
        "Test"
    };
    label.dirty = true;
    TextureManager::loadLabel(label);

    float titleX = w / 2.0f - 300 / 2.0f - 20;
    float titleY = h / 4.0f - 65 / 2.0f;

    title.addComponent<Label>(label);
    title.addComponent<Transform>(Vector2D{titleX, titleY}, 0.0, 1.0);
    titleEntity = &title;
}

void MainMenuScene::setupHowToPanel(int w, int h) {
   if (howToPanel) return;

    // ================================
    // PANEL BACKGROUND
    // ================================
    auto& panel = world.createEntity();
    float panelWidth  = w / 2.0f;
    float panelHeight = h;
    float panelX      = (w - panelWidth) / 2.0f;
    float panelY      = (h - panelHeight) / 2.0f;

    panel.addComponent<Transform>(Vector2D{panelX, panelY}, 0.0f, 1.0f);
    panel.addComponent<Collider>("ui", SDL_FRect{panelX, panelY, panelWidth, panelHeight});

    SDL_Texture* panelTex = TextureManager::load("../asset/sprites/panel_background.png");
    SDL_FRect panelSrc {0, 0, 37, 39};
    SDL_FRect panelDest {panelX, panelY, panelWidth, panelHeight};
    panel.addComponent<Sprite>(panelTex, panelSrc, panelDest);
    panel.getComponent<Sprite>().visible = false;
    panel.getComponent<Sprite>().renderLayer = RenderLayer::UI;

    howToPanel = &panel;

    // ================================
    // HELPER FUNCTION TO CREATE TEXT
    // ================================
    auto makeText = [&](const std::string& msg, float x, float y, float scale, SDL_Color color = {230,230,230,255}, const std::string& cacheKey = "") -> Entity* {
        auto& e = world.createEntity();
        Label L {
            msg,
            AssetManager::getFont("Arial"),
            color,
            LabelType::PlayerPosition,
            cacheKey.empty() ? msg : cacheKey
        };
        L.dirty = true;
        TextureManager::loadLabel(L);

        e.addComponent<Label>(L);
        e.addComponent<Transform>(Vector2D{x, y}, 0.0f, scale);
        e.getComponent<Label>().visible = false;
        howToTextEntities.push_back(&e);
        return &e;
    };

    // ================================
    // HEADER
    // ================================
    makeText("HOW TO PLAY", panelX + 220, panelY + 100, 1.3f, {255,255,255,255}, "header_label");

    // ================================
    // INSTRUCTION LINES
    // ================================
    makeText("Collect all  -     to progress", panelX + 120, panelY + 160, 1.1f);
    makeText("Avoid  -     with WASD",       panelX + 120, panelY + 240, 1.1f);
    makeText("Parry        with F",          panelX + 120, panelY + 320, 1.1f);
    makeText("Show Debug Collider - C",panelX + 120, panelY + 400, 1.1f);
    makeText("Go back to the main menu - ESC", panelX + 120, panelY + 480, 1.1f);

    // ================================
    // OBJECTS ON ___
    // ================================
    // Coin in first line
    auto& coin = world.createEntity();
    coin.addComponent<Transform>(Vector2D{panelX + 243, panelY + 160}, 0.0f, 1.2f);
    SDL_Texture* coinTex = TextureManager::load("../asset/coin.png");
    SDL_FRect coinSrc {0,0,32,32};
    SDL_FRect coinDest {panelX + 230 - 16, panelY + 170 - 16, 32, 32};
    coin.addComponent<Sprite>(coinTex, coinSrc, coinDest);
    coin.getComponent<Sprite>().visible = false;
    coin.getComponent<Sprite>().renderLayer = RenderLayer::UI;
    coin.addComponent<ProjectileType>(ProjectileType::Bullet);
    howToTextEntities.push_back(&coin);

    // Sawblade in second line
    auto& saw = world.createEntity();
    saw.addComponent<Transform>(Vector2D{panelX + 193, panelY + 233}, 0.0f, 1.5f);
    SDL_Texture* sawTex = TextureManager::load("../animations/saw_blade.png");
    SDL_FRect sawSrc {0,0,25.6f,25.6f};
    SDL_FRect sawDest {panelX + 240 - 25.6f/2, panelY + 250 - 25.6f/2, 25.6f, 25.6f};
    saw.addComponent<Sprite>(sawTex, sawSrc, sawDest);
    Animation sawAnim = AssetManager::getAnimation("sawblade");
    saw.addComponent<Animation>(sawAnim);
    saw.addComponent<Velocity>(Vector2D(0.f,0.f), 0.0f);
    saw.getComponent<Sprite>().visible = false;
    saw.getComponent<Sprite>().renderLayer = RenderLayer::UI;
    saw.addComponent<ProjectileTag>();
    saw.addComponent<ProjectileType>(ProjectileType::Sawblade);
    howToTextEntities.push_back(&saw);

    // Bullet in third line
    auto& bullet = world.createEntity();
    bullet.addComponent<Transform>(Vector2D{panelX + 189, panelY + 312}, 0.0f, 1.5f);
    SDL_Texture* bulletTex = TextureManager::load("../animations/saw_blade.png");
    SDL_FRect bulletSrc {0,0,25.6f,25.6f};
    SDL_FRect bulletDest {panelX + 200 - 25.6f/2, panelY + 330 - 25.6f/2, 25.6f, 25.6f};
    bullet.addComponent<Sprite>(bulletTex, bulletSrc, bulletDest);
    Animation bulletAnim = AssetManager::getAnimation("sawblade");
    bullet.addComponent<Animation>(bulletAnim);
    bullet.addComponent<Velocity>(Vector2D(0.f,0.f), 0.0f);
    bullet.getComponent<Sprite>().visible = false;
    bullet.getComponent<Sprite>().renderLayer = RenderLayer::UI;
    bullet.addComponent<ProjectileTag>();
    bullet.addComponent<ProjectileType>(ProjectileType::Bullet);
    howToTextEntities.push_back(&bullet);

}
