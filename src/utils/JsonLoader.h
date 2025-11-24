//
// Created by richa on 2025-11-23.
//

#ifndef TEST_JSONLOADER_H
#define TEST_JSONLOADER_H
#include <string>
#include <vector>
#include "Vector2D.h"
// #include <nlohmann/json.hpp>
#include "Component.h"
#include "vendor/json.hpp"

struct SawbladeConfig {
    Vector2D pointA;
    Vector2D pointB;
    float speed;
    float scale;
    bool stationary;
    SawbladeMotionType motionType;


    Vector2D center;
    float radius;
    float angularSpeed;
    float angle;
    bool clockwise;
};

class JsonLoader {
public:
    static std::vector<SawbladeConfig> loadSawblades(const std::string& sceneName);
};
#endif //TEST_JSONLOADER_H