//
// Created by richa on 2025-11-26.
//

#ifndef TEST_LIFETIMESYSTEM_H
#define TEST_LIFETIMESYSTEM_H
class LifetimeSystem {
public:
    void update(std::vector<std::unique_ptr<Entity>>& entities, float dt) {
        for (auto it = entities.begin(); it != entities.end(); ) {
            auto& entity = *it;
            if (entity->hasComponent<Lifetime>()) {
                auto& life = entity->getComponent<Lifetime>();
                life.timeRemaining -= dt;
                if (life.timeRemaining <= 0.0f) {
                    // Remove entity
                    it = entities.erase(it); // or call deferred destroy
                    continue;
                }
            }
            ++it;
        }
    }
};
#endif //TEST_LIFETIMESYSTEM_H