//
// Created by richa on 2025-10-21.
//

#include "Scene.h"

#include "AssetManager.h"
#include "JsonLoader.h"

Scene::Scene(const std::string& sceneName, const char* mapPath, const int windowWidth, const int windowHeight, bool isLevel) : name(sceneName) {
    world.getMap().load(mapPath, TextureManager::load("../asset/Dungeon_Tileset_at.png"));
    initCamera(windowWidth, windowHeight);

    if (!isLevel) return;

    initCoins();
    initPlayer();
    initColliders();
    initBulletSpawner();
    createSawBlades(sceneName);

    auto &state(world.createEntity());
    auto &sceneState = state.addComponent<SceneState>();
    sceneState.requiredCoins = world.getMap().itemSpawns.size();



}

void Scene::createSawBlades(const std::string& sceneName) {
    auto sawConfigs = JsonLoader::loadSawblades(sceneName);
    for (auto& s : sawConfigs) {
        auto& saw = world.createEntity();
        Vector2D startPos;
        if (s.motionType == SawbladeMotionType::Linear) {
            startPos = s.waypoints.empty() ? Vector2D(0,0) : s.waypoints[0];
        } else if (s.motionType == SawbladeMotionType::Circular) {
            // For circular, the starting position is computed from the first circular action
            if (!s.actions.empty()) {
                auto& a = s.actions[0]; // assume first action defines the circular motion
                startPos.x = s.waypoints[0].x + a.radius; // or compute using cos(angle)
                startPos.y = s.waypoints[0].y;           // for now, start at center + radius
            } else {
                startPos = s.waypoints.empty() ? Vector2D(0,0) : s.waypoints[0];
            }
        }

        auto& t = saw.addComponent<Transform>(startPos, 0.0f, s.scale);

        // Sprite
        SDL_Texture* sawTex = TextureManager::load("../animations/saw_blade.png");
        SDL_FRect src {0, 0, 25.6f, 25.6f};
        SDL_FRect dest {
            t.position.x - 25.6f / 2.0f,
            t.position.y - 25.6f / 2.0f,
            25.6f,
            25.6f
        };
        saw.addComponent<Sprite>(sawTex, src, dest);

        // Animation
        Animation sawAnim = AssetManager::getAnimation("sawblade");
        saw.addComponent<Animation>(sawAnim);

        // Velocity (optional)
        saw.addComponent<Velocity>(Vector2D(0.f, 0.f), 0.0f);

        // Sawblade path
        auto& path = saw.addComponent<SawbladePath>();
        path.actions.clear();
        path.speed = s.speed;
        path.stationary = s.stationary;
        path.motionType = s.motionType;
        for (auto& a : s.actions) {
            WaypointAction wa;
            wa.switchToLinear = a.switchToLinear;
            wa.switchToCircular = a.switchToCircular;
            wa.radius = a.radius;
            wa.angularSpeed = a.angularSpeed;
            wa.clockwise = a.clockwise;
            path.actions.push_back(wa);
        }
        if (s.motionType == SawbladeMotionType::Linear) {
            path.waypoints = s.waypoints;
        } else if (s.motionType == SawbladeMotionType::Circular) {
            if (!s.waypoints.empty() && !s.actions.empty()) {
                path.center = s.waypoints[0];
                path.radius = s.actions[0].radius;
                path.angularSpeed = s.actions[0].angularSpeed;
                path.clockwise = s.actions[0].clockwise;
                path.angle = 0.0f;
                path.rotationAcc = 0.0f;
            }

        }

        // Collider
        Collider& c = saw.addComponent<Collider>("projectile");
        c.scaleOffset = 0.65f;
        c.positionOffset = {12.5f, 20.0f};
        c.baseW = 25.6;
        c.baseH = 25.6;
        saw.addComponent<ProjectileTag>();
        saw.addComponent<ProjectileType>(ProjectileType::Sawblade);
    }
}


void Scene::initCamera(int windowWidth, int windowHeight) {
    auto& cam = world.createEntity();
    SDL_FRect camView{};
    camView.w = windowWidth;
    camView.h = windowHeight;
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);
}

void Scene::initPlayer() {
    auto& player(world.createEntity());
    playerEntity = &player;
    auto& playerTransform = player.addComponent<Transform>(world.getMap().playerSpawn, 0.0f, 1.0f);
    world.setRespawn(world.getMap().playerSpawn);

    player.addComponent<Velocity>(Vector2D(0.f, 0.f), 150.0f);
    SDL_Texture* tex = TextureManager::load("../asset/Fine.svg");
    SDL_FRect playerSrc {0,0,36,36};
    SDL_FRect playerDst {playerTransform.position.x, playerTransform.position.y,36,36};
    player.addComponent<Sprite>(tex, playerSrc, playerDst);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.scaleOffset = 0.7f;
    playerCollider.baseH = 36.0f;
    playerCollider.baseW = 36.0f;
    playerCollider.positionOffset.x = 18.0f;
    playerCollider.positionOffset.y = 18.0f;

    player.addComponent<PlayerTag>();
    player.addComponent<ParryInput>();
}

void Scene::initColliders() {
    for (auto &collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto& c = e.addComponent<Collider>();

        if (collider.tag == "next_level") {
            c.tag = "next_level";
        } else {
            c.tag = "wall";
        }

        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;
    }
}

void Scene::initCoins() {
    SDL_Texture* itemTex = TextureManager::load("../asset/coin.png");
    for (auto &spawnPoint : world.getMap().itemSpawns) {
        auto& item = world.createEntity();
        auto& itemTransform = item.addComponent<Transform>(
            Vector2D(spawnPoint.x, spawnPoint.y), 0.0f, 1.0f);

        SDL_FRect itemSrc{0, 0, 32, 32};
        SDL_FRect itemDest {itemTransform.position.x, itemTransform.position.y, 32, 32};
        item.addComponent<CoinTag>();
        item.addComponent<Coin>();
        item.addComponent<Sprite>(itemTex, itemSrc, itemDest);
        auto& itemCollider = item.addComponent<Collider>("item");
        itemCollider.rect.w = itemDest.w;
        itemCollider.rect.h = itemDest.h;

    }
}

void Scene::initBulletSpawner() {
    auto& spawner(world.createEntity());
    spawner.addComponent<TimedSpawner>(5.0f, [this] {
        auto& bulletSpawns = world.getMap().bulletSpawnAreas;
        if (bulletSpawns.size() == 0) return;

        int index = rand() % bulletSpawns.size();
        Vector2D spawnPos = bulletSpawns[index];
        auto& bullet = world.createDeferredEntity();
        auto& t = bullet.addComponent<Transform>(spawnPos, 0.0f, 2.0f);
        SDL_Texture* sawTex = TextureManager::load("../animations/saw_blade.png");
        SDL_FRect src {3, 33, 25.6f, 25.6f};
        SDL_FRect dest {
            t.position.x - 25.6f / 2.0f,
            t.position.y - 25.6f / 2.0f,
            25.6f,
            25.6f
        };
    bullet.addComponent<Sprite>(sawTex, src, dest);
    Vector2D playerPos = playerEntity->getComponent<Transform>().position;
    Vector2D dir = playerPos - spawnPos;
    dir.normalize();
    bullet.addComponent<Velocity>(dir, 150.0f);
    Animation sawAnim = AssetManager::getAnimation("sawblade");
    auto& animComp = bullet.addComponent<Animation>(sawAnim);
    animComp.speed = 0.1f;
    auto& c = bullet.addComponent<Collider>("projectile");
    bullet.addComponent<ProjectileType>(ProjectileType::Bullet);
    c.scaleOffset = 0.65f;
    c.positionOffset = {12.5f, 20.0f};
    c.baseW = 25.6;
    c.baseH = 25.6;
    bullet.addComponent<Lifetime>(20.0);
    bullet.addComponent<ProjectileTag>();
    bullet.addComponent<Parryable>(Parryable::Type::Reflect);
    });
}