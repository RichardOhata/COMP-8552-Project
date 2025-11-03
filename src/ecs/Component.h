//
// Created by richa on 2025-09-16.
//

#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H
#include <functional>
#include <SDL3/SDL_rect.h>

#include "Vector2D.h"
#include "TextureManager.h"
#include "AnimationClip.h"
#include <string>

struct Transform {
    Vector2D position{};
    float rotation{};
    float scale{};
    Vector2D oldPosition{};
};

struct Velocity {
    Vector2D direction{};
    float speed{};
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dst{};
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
};

struct Animation {
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float time{};
    int currentFrame{};
    float speed = 0.1f;
};

struct Camera {
    SDL_FRect view;
    float worldWidth;
    float worldHeight;
};

struct TimedSpawner {
    float spawnInterval{};
    std::function<void()> spawnCallback{};
    float timer{};
};


struct SceneState {
    int coinsCollected = 0;
};

struct PlayerTag{};
struct ProjectileTag{};
#endif //TEST_COMPONENT_H