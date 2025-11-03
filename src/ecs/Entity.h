//
// Created by richa on 2025-09-16.
//

#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H
#include <bitset>
#include <cstddef>
#include <array>
#include "ComponentType.h"

constexpr std::size_t MAX_COMPONENTS = 32;

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

using ComponentArray = std::array<void*, MAX_COMPONENTS>;

class Entity {
    bool active = true;
    ComponentArray componentArray{};
    ComponentBitSet componentBitSet{};
public:
    bool isActive() {
        return active;
    }

    void destroy() {
        active = false;
    }

    template <typename T>
    bool hasComponent() {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename... nArgs>
    T& addComponent(nArgs&&... args) {
        T* component(new T(std::forward<nArgs>(args)...));

        componentArray[getComponentTypeID<T>()] = component;

        componentBitSet[getComponentTypeID<T>()] = true;
        return *component;
    }

    template <typename T>
    T& getComponent() {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    template <typename T>
    void deactivateComponent() {
        componentBitSet[getComponentTypeID<T>()] = false;
    }
};
#endif //TEST_ENTITY_H
