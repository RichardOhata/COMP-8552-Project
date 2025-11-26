//
// Created by richa on 2025-10-21.
//

#include "Scene.h"

#include "AssetManager.h"
#include "JsonLoader.h"

Scene::Scene(const char* sceneName, const char* mapPath, const int windowWidth, const int windowHeight, bool isLevel) : name(sceneName) {
    world.getMap().load(mapPath, TextureManager::load("../asset/Dungeon_Tileset_at.png"));
    auto& cam = world.createEntity();
    SDL_FRect camView{};
    camView.w = windowWidth;
    camView.h = windowHeight;
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);
    if (!isLevel) return;
    createSawBlades(sceneName);
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
        auto& player(world.createEntity());
        auto& playerTransform = player.addComponent<Transform>(world.getMap().playerSpawn, 0.0f, 1.0f);
        world.setRespawn(world.getMap().playerSpawn);
        player.addComponent<Velocity>(Vector2D(0.f, 0.f), 150.0f);


        // SDL_Texture* tex = TextureManager::load("../animations/bull_anim.png");
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


        // Creates enemy spwaner entity
        // auto& spawner(world.createEntity());
        // Transform t = spawner.addComponent<Transform>(Vector2D(windowWidth/2, windowHeight - 5), 0.0f, 1.0f);
        // spawner.addComponent<TimedSpawner>(2.0f, [this, t] {
        //
        //     auto& e(world.createDeferredEntity());
        //     e.addComponent<Transform>(Vector2D(t.position.x, t.position.y), 0.0f, 1.0f);
        //     e.addComponent<Velocity>(Vector2D(0.f, -1.f), 100.0f);
        //
        //     Animation anim = AssetManager::getAnimation("enemy");
        //     e.addComponent<Animation>(anim);
        //
        //     SDL_Texture* tex = TextureManager::load("../animations/bird_anim.png");
        //     SDL_FRect src {0, 0, 32, 32};
        //     SDL_FRect dest {t.position.x, t.position.y, 32, 32};
        //     e.addComponent<Sprite>(tex, src, dest);
        //
        //     Collider c = e.addComponent<Collider>("projectile");
        //     c.rect.w = dest.w;
        //     c.rect.h = dest.h;
        //
        //     e.addComponent<ProjectileTag>();
        // });

        auto &state(world.createEntity());
        auto &sceneState = state.addComponent<SceneState>();
        sceneState.requiredCoins = world.getMap().itemSpawns.size();
}

void Scene::createSawBlades(const char* sceneName) {
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
        if (s.motionType == SawbladeMotionType::Linear) {
            path.waypoints = s.waypoints;
            for (auto& a : s.actions) {
                WaypointAction wa;
                wa.switchToLinear = a.switchToLinear;
                path.actions.push_back(wa);
            }
        } else if (s.motionType == SawbladeMotionType::Circular) {
            if (!s.actions.empty()) {
                auto& a = s.actions[0];
                path.center = s.waypoints[0]; // center
                path.radius = a.radius;
                path.angularSpeed = a.angularSpeed;
                path.clockwise = a.clockwise;
            }
        }

        // Collider
        Collider& c = saw.addComponent<Collider>("projectile");
        c.scaleOffset = 0.65f;
        c.positionOffset = {12.5f, 20.0f};
        c.baseW = 25.6;
        c.baseH = 25.6;
        saw.addComponent<ProjectileTag>();
    }
}





// Entity &Scene::createSawblade(Vector2D pointA, Vector2D pointB, float speed, float scale, bool stationary) {
//     auto& sawBlade(world.createEntity());
//     Transform sawTrans = sawBlade.addComponent<Transform>(
//           Vector2D(pointA.x + 25.6f / 2.0f, pointA.y + 25.6f / 2.0f),
//           0.0f,
//           scale
//       );
//
//     SDL_Texture* sawTex = TextureManager::load("../animations/saw_blade.png");
//     SDL_FRect src {0, 0, 25.6f, 25.6f};
//     SDL_FRect dest {
//         sawTrans.position.x - 25.6f / 2.0f,
//         sawTrans.position.y - 25.6f / 2.0f,
//         25.6f,
//         25.6f
//     };
//     sawBlade.addComponent<Sprite>(sawTex, src, dest);
//     Animation sawAnim = AssetManager::getAnimation("sawblade");
//     sawBlade.addComponent<Animation>(sawAnim);
//     sawBlade.addComponent<Velocity>(Vector2D(0.f, 0.f), 0.0f);
//     sawBlade.addComponent<SawbladePath>(pointA, pointB, speed, true, stationary);
//     Collider& c = sawBlade.addComponent<Collider>("projectile");
//     c.scaleOffset = 0.65f;
//     c.positionOffset.x = 12.5f;
//     c.positionOffset.y = 20.0f;
//     c.baseW = 25.6;
//     c.baseH = 25.6;
//     sawBlade.addComponent<ProjectileTag>();
//
//     return sawBlade;
// }
//
// Entity &Scene::createCircularSawblade(Vector2D center, float radius, float angularSpeed, float angle, float scale, bool clockwise) {
//     auto& saw(world.createEntity());
//
//     // Compute initial position
//     float px = center.x + std::cos(angle) * radius;
//     float py = center.y + std::sin(angle) * radius;
//
//     auto& t = saw.addComponent<Transform>(
//         Vector2D(px, py),
//         0.0f,
//         scale
//     );
//
//     SDL_Texture* sawTex = TextureManager::load("../animations/saw_blade.png");
//     SDL_FRect src {0, 0, 25.6f, 25.6f};
//     SDL_FRect dest {
//         t.position.x - 25.6f / 2.0f,
//         t.position.y - 25.6f / 2.0f,
//         25.6f,
//         25.6f
//     };
//
//     saw.addComponent<Sprite>(sawTex, src, dest);
//
//     Animation anim = AssetManager::getAnimation("sawblade");
//     saw.addComponent<Animation>(anim);
//
//     saw.addComponent<Velocity>(Vector2D(0,0), 0.0f);
//
//     auto& path = saw.addComponent<SawbladePath>();
//     path.motionType = SawbladeMotionType::Circular;
//     path.center = center;
//     path.radius = radius;
//     path.angle = angle;
//     path.angularSpeed = angularSpeed;
//     path.clockwise = clockwise;
//     auto& c = saw.addComponent<Collider>("projectile");
//     c.scaleOffset = 0.65f;
//     c.positionOffset = {12.5f, 20.0f};
//     c.baseW = 25.6f;
//     c.baseH = 25.6f;
//
//     saw.addComponent<ProjectileTag>();
//
//     return saw;
// }



