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
    float originalWidth = 0;
    float originalHeight = 0;
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
    float baseW;
    float baseH;
    float scaleOffset = 1.0f;
    Vector2D positionOffset{0.f, 0.f};
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
    int requiredCoins = 0;
};

enum class SawbladeMotionType {
    Linear,
    Circular
};

// Component for sawblade movement
struct SawbladePath {
    Vector2D pointA;
    Vector2D pointB;
    float speed = 0.0;
    bool forward = true;
    bool stationary = false;
    Vector2D center;
    float radius = 0.0f;
    float angularSpeed = 0.0f;
    float angle = 0.0f;
    bool clockwise = false;



    SawbladeMotionType motionType = SawbladeMotionType::Linear;
};

struct Coin {
    bool collected = false;
};

struct PlayerTag{};
struct ProjectileTag{};
struct CoinTag{};
#endif //TEST_COMPONENT_H