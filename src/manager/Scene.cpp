//
// Created by richa on 2025-10-21.
//

#include "Scene.h"

#include "AssetManager.h"

Scene::Scene(const char* sceneName, const char* mapPath, const int windowWidth, const int windowHeight) : name(sceneName) {
    world.getMap().load(mapPath, TextureManager::load("../asset/spritesheet.png"));
    for (auto &collider : world.getMap().colliders) {
        auto& e = world.createEntity();
        e.addComponent<Transform>(Vector2D(collider.rect.x, collider.rect.y), 0.0f, 1.0f);
        auto& c = e.addComponent<Collider>("wall");
        c.rect.x = collider.rect.x;
        c.rect.y = collider.rect.y;
        c.rect.w = collider.rect.w;
        c.rect.h = collider.rect.h;

        SDL_Texture* tex = TextureManager::load("../asset/spritesheet.png");
        SDL_FRect colSrc {0, 32, 32, 32};
        SDL_FRect colDst {c.rect.x, c.rect.y, c.rect.w, c.rect.h};
        e.addComponent<Sprite>(tex, colSrc, colDst);
    }
    // Assignment 6
    SDL_Texture* itemTex = TextureManager::load("../asset/coin.png");
    for (auto &spawnPoint : world.getMap().itemSpawns) {
        auto& item = world.createEntity();
        auto& itemTransform = item.addComponent<Transform>(
            Vector2D(spawnPoint.x, spawnPoint.y), 0.0f, 1.0f);

        SDL_FRect itemSrc{0, 0, 32, 32};
        SDL_FRect itemDest {itemTransform.position.x, itemTransform.position.y, 32, 32};

        item.addComponent<Sprite>(itemTex, itemSrc, itemDest);
        auto& itemCollider = item.addComponent<Collider>("item");
        itemCollider.rect.w = itemDest.w;
        itemCollider.rect.h = itemDest.h;
    }

    // auto& item(world.createEntity());
    // auto& itemTransform = item.addComponent<Transform>(Vector2D(100, 200), 0.0f, 1.0f);
    //
    // // SDL_Texture* itemTex = TextureManager::load("../asset/coin.png");
    // SDL_FRect itemSrc{0, 0, 32, 32};
    //
    // SDL_FRect itemDest {itemTransform.position.x, itemTransform.position.y, 32, 32};
    //
    // item.addComponent<Sprite>(itemTex, itemSrc, itemDest);
    //
    // auto& itemCollider = item.addComponent<Collider>("item");
    // itemCollider.rect.w = itemDest.w;
    // itemCollider.rect.h = itemDest.h;

    // Assignment 5:
    auto& item2(world.createEntity());
    auto& item2Transform = item2.addComponent<Transform>(Vector2D(200, 200), 0.0f, 1.0f);
    SDL_Texture* itemTex2 = TextureManager::load("../asset/ball.png");
    SDL_FRect item2Src{0, 0, 32, 32};
    SDL_FRect item2Dest {item2Transform.position.x, item2Transform.position.y, 32, 32};
    item2.addComponent<Sprite>(itemTex2, item2Src, item2Dest);
    auto& item2Collider = item2.addComponent<Collider>("item2");
    item2Collider.rect.w = item2Dest.w;
    item2Collider.rect.h = item2Dest.h;

    auto& cam = world.createEntity();
    SDL_FRect camView{};
    camView.w = windowWidth;
    camView.h = windowHeight;
    cam.addComponent<Camera>(camView, world.getMap().width * 32, world.getMap().height * 32);

    auto& player(world.createEntity());
    auto& playerTransform = player.addComponent<Transform>(Vector2D(0, 0), 0.0f, 1.0f);
    player.addComponent<Velocity>(Vector2D(0.f, 0.f), 200.0f);


    Animation anim = AssetManager::getAnimation("player");
    player.addComponent<Animation>(anim);

    // SDL_Texture* tex = TextureManager::load("../animations/bull_anim.png");
    SDL_Texture* tex = TextureManager::load("../animations/CATSPRITESHEET_Gray.png");
    // SDL_FRect playerSrc {0,0,32,44};
    SDL_FRect playerSrc = anim.clips[anim.currentClip].frameIndicies[0];
    SDL_FRect playerDst {playerTransform.position.x, playerTransform.position.y,64,88};
    player.addComponent<Sprite>(tex, playerSrc, playerDst);

    auto& playerCollider = player.addComponent<Collider>("player");
    playerCollider.rect.w = playerDst.w;
    playerCollider.rect.h = playerDst.h;

    player.addComponent<PlayerTag>();

    auto& spawner(world.createEntity());
    Transform t = spawner.addComponent<Transform>(Vector2D(windowWidth/2, windowHeight - 5), 0.0f, 1.0f);
    spawner.addComponent<TimedSpawner>(2.0f, [this, t] {

        auto& e(world.createDeferredEntity());
        e.addComponent<Transform>(Vector2D(t.position.x, t.position.y), 0.0f, 1.0f);
        e.addComponent<Velocity>(Vector2D(0.f, -1.f), 100.0f);

        Animation anim = AssetManager::getAnimation("enemy");
        e.addComponent<Animation>(anim);

        SDL_Texture* tex = TextureManager::load("../animations/bird_anim.png");
        SDL_FRect src {0, 0, 32, 32};
        SDL_FRect dest {t.position.x, t.position.y, 32, 32};
        e.addComponent<Sprite>(tex, src, dest);

        Collider c = e.addComponent<Collider>("projectile");
        c.rect.w = dest.w;
        c.rect.h = dest.h;

        e.addComponent<ProjectileTag>();
    });

    auto &state(world.createEntity());
    state.addComponent<SceneState>();
}
