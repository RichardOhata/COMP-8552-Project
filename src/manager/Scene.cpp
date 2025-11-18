//
// Created by richa on 2025-10-21.
//

#include "Scene.h"

#include "AssetManager.h"

Scene::Scene(const char* sceneName, const char* mapPath, const int windowWidth, const int windowHeight) : name(sceneName) {
    world.getMap().load(mapPath, TextureManager::load("../asset/Dungeon_Tileset_at.png"));
    for (auto &collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto& c = e.addComponent<Collider>("wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        // SDL_Texture* tex = TextureManager::load("../asset/spritesheet.png");
        // SDL_FRect colSrc {0, 32, 32, 32};
        // SDL_FRect colDst {c.rect.x, c.rect.y, c.rect.w, c.rect.h};
        // e.addComponent<Sprite>(tex, colSrc, colDst);
    }



    auto& entity = world.createEntity();
    auto& col = entity.addComponent<Collider>();
    col = world.getMap().nextAreaZone;
    col.tag = "next_level";


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


    auto& cam = world.createEntity();
    SDL_FRect camView{};
    camView.w = windowWidth;
    camView.h = windowHeight;
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);

    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(world.getMap().playerSpawn, 0.0f, 1.0f);
    world.setRespawn(world.getMap().playerSpawn);
    player.addComponent<Velocity>(Vector2D(0.f, 0.f), 150.0f);

    // Animation anim = AssetManager::getAnimation("player");
    // player.addComponent<Animation>(anim);

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

    createSawblade({420, 160}, {425, 500}, 300.0f, 4.0f, false);
    createSawblade({520, 500}, {520, 160}, 300.0f, 4.0f, false);
    createSawblade({625, 160}, {625, 500}, 300.0f, 4.0f, false);
    createSawblade({725, 500}, {725, 160}, 300.0f, 4.0f, false);
    createSawblade({825, 160}, {825, 500}, 300.0f, 4.0f, false);

    createSawblade({350.0f, 160}, {}, 200.0f, 5.0f, true);
    createSawblade({456.0f, 160}, {}, 200.0f, 5.0f, true);
    createSawblade({562.0f, 160}, {}, 200.0f, 5.0f, true);
    createSawblade({668.0f, 160}, {}, 200.0f, 5.0f, true);
    createSawblade({774.0f, 160}, {}, 200.0f, 5.0f, true);
    createSawblade({880.0f, 160}, {}, 200.0f, 5.0f, true);

    createSawblade({350.0f, 510}, {}, 200.0f, 5.0f, true);
    createSawblade({456.0f, 510}, {}, 200.0f, 5.0f, true);
    createSawblade({562.0f, 510}, {}, 200.0f, 5.0f, true);
    createSawblade({668.0f, 510}, {}, 200.0f, 5.0f, true);
    createSawblade({774.0f, 510}, {}, 200.0f, 5.0f, true);
    createSawblade({880.0f, 510}, {}, 200.0f, 5.0f, true);

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
    std::cout << sceneState.requiredCoins << std::endl;
}

Entity &Scene::createSawblade(Vector2D pointA, Vector2D pointB, float speed, float scale, bool stationary) {
    auto& sawBlade(world.createEntity());
    Transform sawTrans = sawBlade.addComponent<Transform>(
          Vector2D(pointA.x + 25.6f / 2.0f, pointA.y + 25.6f / 2.0f),
          0.0f,
          scale
      );

    // Sprite = draw from top-left
    SDL_Texture* sawTex = TextureManager::load("../animations/saw_blade.png");
    SDL_FRect src {0, 0, 25.6f, 25.6f};
    SDL_FRect dest {
        sawTrans.position.x - 25.6f / 2.0f,
        sawTrans.position.y - 25.6f / 2.0f,
        25.6f,
        25.6f
    };
    sawBlade.addComponent<Sprite>(sawTex, src, dest);
    Animation sawAnim = AssetManager::getAnimation("sawblade");
    sawBlade.addComponent<Animation>(sawAnim);
    sawBlade.addComponent<Velocity>(Vector2D(0.f, 0.f), 0.0f);
    sawBlade.addComponent<SawbladePath>(pointA, pointB, speed, true, stationary);
    Collider& c = sawBlade.addComponent<Collider>("projectile");
    c.scaleOffset = 0.65f;
    c.positionOffset.x = 12.5f;
    c.positionOffset.y = 20.0f;
    c.baseW = 25.6;
    c.baseH = 25.6;
    sawBlade.addComponent<ProjectileTag>();

    return sawBlade;
}



