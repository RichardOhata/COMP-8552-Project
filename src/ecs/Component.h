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

#include "Entity.h"

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

enum class RenderLayer {
    World,
    UI
};

struct Sprite {
    SDL_Texture* texture = nullptr;
    SDL_FRect src{};
    SDL_FRect dst{};
    float originalWidth = 0;
    float originalHeight = 0;
    RenderLayer renderLayer = RenderLayer::World;
    bool visible = true;
};

struct Collider {
    std::string tag;
    SDL_FRect rect{};
    float baseW;
    float baseH;
    float scaleOffset = 1.0f;
    Vector2D positionOffset{0.f, 0.f};
    bool enabled = true;
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
struct WaypointAction {
    bool switchToCircular = false;
    bool switchToLinear = false;

    float radius = 0.0f;
    float angularSpeed = 0.0f;
    bool clockwise = true;
};
// Component for sawblade movement
struct SawbladePath {
    // Linear
    float speed = 0.0;
    bool forward = true;
    bool stationary = false;

    // Circular
    Vector2D center;
    float radius = 0.0f;
    float angularSpeed = 0.0f;
    float angle = 0.0f;
    bool clockwise = false;
    float rotationAcc = 0.0f;

    SawbladeMotionType motionType = SawbladeMotionType::Linear;

    std::vector<Vector2D> waypoints;
    std::vector<WaypointAction> actions;
    int currentIndex = 0;
    Vector2D targetPosition;
    bool currentlyAdjusting = false;
};

struct Lifetime {
    float timeRemaining;
};

struct Parryable {
    enum class Type { Destroy, Reflect };
    Type parryType;

    Parryable(Type t = Type::Destroy) : parryType(t) {}
};

struct ParryInput {
    float cooldown = 0.5f;
    float timer = 0.0f;
    bool active = false;
    bool parryPressed = false;
    float parryRange = 75.0f;
    bool onCooldown = false;
};

struct Coin {
    bool collected = false;
};

struct Clickable {
    std::function<void()> onPressed{};
    std::function<void()> onReleased{};
    std::function<void()> onCancel{};
    bool pressed = false;
    bool hovered = false;
    bool clicked = false;

    std::function<void()> onClick = nullptr;
};

struct Parent {
    Entity* parent = nullptr;
};

struct Children {
    std::vector<Entity*> children{};
};
struct ProjectileType {
    enum Type { Sawblade, Bullet } type;
    bool preventHoming = false;
};

struct PlayerTag{};
struct ProjectileTag{};
struct CoinTag{};
#endif //TEST_COMPONENT_H