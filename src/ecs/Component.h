//
// Created by richa on 2025-09-16.
//

#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL3/SDL_rect.h>
#include "SDL3_ttf/SDL_ttf.h"
#include "Vector2D.h"
#include "../manager/TextureManager.h"
#include "AnimationClip.h"
#include "Entity.h"

// ----------------------------
// Core Transform Components
// ----------------------------
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

// ----------------------------
// Rendering Components
// ----------------------------
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

// ----------------------------
// Physics / Collision
// ----------------------------
struct Collider {
    std::string tag;
    SDL_FRect rect{};
    float baseW;
    float baseH;
    float scaleOffset = 1.0f;
    Vector2D positionOffset{0.f, 0.f};
    bool enabled = true;
};

// ----------------------------
// Animation
// ----------------------------
struct Animation {
    std::unordered_map<std::string, AnimationClip> clips{};
    std::string currentClip{};
    float time{};
    int currentFrame{};
    float speed = 0.1f;
};

// ----------------------------
// Camera
// ----------------------------
struct Camera {
    SDL_FRect view;
    float worldWidth;
    float worldHeight;
};

// ----------------------------
// Spawning / Lifetime
// ----------------------------
struct TimedSpawner {
    float spawnInterval{};
    std::function<void()> spawnCallback{};
    float timer{};
};

struct Lifetime {
    float timeRemaining;
};

// ----------------------------
// Scene State
// ----------------------------
struct SceneState {
    int coinsCollected = 0;
    int requiredCoins = 0;
};

// ----------------------------
// Sawblade / Pathing
// ----------------------------
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

// ----------------------------
// Combat / Player
// ----------------------------
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
    float parryRange = 60.0f;
    bool onCooldown = false;
};

// ----------------------------
// Collectibles
// ----------------------------
struct Coin {
    bool collected = false;
};

// ----------------------------
// UI / Interaction
// ----------------------------
struct Clickable {
    std::function<void()> onPressed{};
    std::function<void()> onReleased{};
    std::function<void()> onCancel{};
    std::function<void()> onClick = nullptr;

    bool pressed = false;
    bool hovered = false;
    bool clicked = false;
};

enum class LabelType {
 PlayerPosition
};

struct Label {
    std::string text{};
    TTF_Font* font = nullptr;
    SDL_Color color {};
    LabelType type = LabelType::PlayerPosition;
    std::string textureCacheKey{};
    SDL_Texture* texture = nullptr;
    SDL_FRect dst{};
    bool visible = true;
    bool dirty = false;
};

// ----------------------------
// Entity Hierarchy
// ----------------------------
struct Parent {
    Entity* parent = nullptr;
};

struct Children {
    std::vector<Entity*> children{};
};

// ----------------------------
// Projectiles
// ----------------------------
struct ProjectileType {
    enum Type { Sawblade, Bullet } type;
    bool preventHoming = false;
};

// ----------------------------
// Tags / Markers
// ----------------------------
struct PlayerTag{};
struct ProjectileTag{};
struct CoinTag{};

#endif // TEST_COMPONENT_H
