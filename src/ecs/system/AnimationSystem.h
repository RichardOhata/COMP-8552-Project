//
// Created by richa on 2025-10-14.
//

#ifndef TEST_ANIMATIONSYSTEM_H
#define TEST_ANIMATIONSYSTEM_H
#include <memory>
#include <iostream>
#include "Component.h"
#include "Entity.h"
class AnimationSystem {
public:
    void update(const std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto& e : entities) {
            if (e->hasComponent<Animation>() && e->hasComponent<Velocity>()) {
                auto& anim = e->getComponent<Animation>();
                auto& velocity = e->getComponent<Velocity>();
                std::string newClip;

                if (velocity.direction.x > 0.0f) newClip = "walk_right";
                else if (velocity.direction.x < 0.0f) newClip = "walk_left";
                else if (velocity.direction.y > 0.0f) newClip = "walk_down";
                else if (velocity.direction.y < 0.0f && e->hasComponent<PlayerTag>()) newClip = "walk_up";
                else if (velocity.direction.y < 0.0f) newClip = "idle_right";
                else {
                    newClip = "idle_down";
                }


                if (newClip != anim.currentClip) {
                    anim.currentClip = newClip;
                    anim.time = 0.0f;
                    anim.currentFrame = 0;
                }

                float animFrameSpeed = anim.speed;
                auto clip = anim.clips[anim.currentClip];

                anim.time += dt;

                if (anim.time >= animFrameSpeed) {
                    anim.time -= animFrameSpeed;

                    std::size_t totalAnimationFrames = clip.frameIndicies.size();
                    anim.currentFrame = (anim.currentFrame + 1) % totalAnimationFrames;
                }
            }
        }
}

};
#endif //TEST_ANIMATIONSYSTEM_H