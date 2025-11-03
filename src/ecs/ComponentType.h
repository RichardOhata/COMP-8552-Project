//
// Created by richa on 2025-09-16.
//

#ifndef TEST_COMPONENTTYPE_H
#define TEST_COMPONENTTYPE_H
#include <cstddef>

using ComponentTypeID = std::size_t;

inline ComponentTypeID getComponentTypeID() {
    static ComponentTypeID id = 0;
    return id++;
}

template <typename T>
ComponentTypeID getComponentTypeID() {
    static ComponentTypeID typeID = getComponentTypeID();
    return typeID;
}
#endif //TEST_COMPONENTTYPE_H
