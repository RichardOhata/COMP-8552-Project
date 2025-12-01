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

struct WaypointActionConfig {
    bool switchToLinear = false;
    bool switchToCircular = false;
    float radius = 0.0f;
    float angularSpeed = 0.0f;
    bool clockwise = true;
};

struct SawbladeConfig {
    float speed = 0.0f;
    float scale = 1.0f;
    bool stationary = false;

    std::vector<Vector2D> waypoints;
    std::vector<WaypointActionConfig> actions;

    SawbladeMotionType motionType = SawbladeMotionType::Linear;
    Vector2D center;
    float radius = 0.0f;
    float angularSpeed = 0.0f;
    float angle = 0.0f;
    bool clockwise = false;
};

struct BulletSpawnerConfig {
    float frequency = 5.0f;
    float speed = 150.0f;
};

class JsonLoader {
public:
    static std::vector<SawbladeConfig> loadSawblades(const std::string& sceneName);

    static BulletSpawnerConfig loadBulletSpawner(const std::string &sceneName);

    static bool isGameCompleted();

    static void setGameCompleted(bool completed);
};
#endif //TEST_JSONLOADER_H