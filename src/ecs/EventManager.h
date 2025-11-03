//
// Created by richa on 2025-09-30.
//

#ifndef TEST_EVENTMANAGER_H
#define TEST_EVENTMANAGER_H
#include <functional>

#include "Entity.h"

struct CollisionEvent {
    Entity* entityA = nullptr;
    Entity* entityB = nullptr;
};

class EventManager {
    public:

    void emit(CollisionEvent event) const {
        for (const auto& listener : collisionListeners) {
            listener(event);
        }
    }
    // template<typename EventType>
    // void emit(const EventType& event) {
    //     //retrieve list of subscribers to certain events
    //     auto& listeners = getListeners<EventType>();
    //     //loop all subscribers to certain events
    //     for (auto& listener : listeners) {
    //         listener(event);
    //     }
    // }

    void subscribe(std::function<void(const CollisionEvent&)> callback) {
        collisionListeners.emplace_back(callback);
    }

    // template<typename EventType>
    // void subscribe(std::function<void(const EventType&)> callback) {
    //     //pass in the callback
    //     getListeners<EventType>().push_back(callback);
    // }


private:
//     template<typename EventType>
//     std::vector<std::function<void(const EventType&)>>& getListeners() {
//         static std::vector<std::function<void(const EventType&)>> listeners;
//         return listeners;
//     }

    std::vector<std::function<void(const CollisionEvent&)>> collisionListeners;
};

#endif //TEST_EVENTMANAGER_H