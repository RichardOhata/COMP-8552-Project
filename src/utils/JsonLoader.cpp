//
// Created by richa on 2025-11-23.
//

#include "JsonLoader.h"
#include <fstream>
#include <iostream>
#include "vendor/json.hpp"
// #include <nlohmann/json.hpp>
#include <filesystem>

#include "config/Config.h"
namespace fs = std::filesystem;

using json = nlohmann::json;

std::vector<SawbladeConfig> JsonLoader::loadSawblades(const std::string& sceneName)
{
    std::vector<SawbladeConfig> result;

    std::string filePath;
    if (Config::LOCAL_BUILD) {
        filePath  = "../level_data/" + sceneName + ".json";
    } else {
        filePath = "level_data/" + sceneName + ".json";
    }

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to load sawblade config file: " << filePath << std::endl;
        return result;
    }

    json data;
    file >> data;

    for (auto& s : data["sawblades"])
    {
        SawbladeConfig cfg;
        cfg.speed = s.value("speed", 0.0f);
        cfg.scale = s.value("scale", 1.0f);
        cfg.stationary = s.value("stationary", false);

        // Load waypoints
        for (auto& wp : s["waypoints"]) {
            cfg.waypoints.emplace_back(Vector2D{wp[0], wp[1]});
        }

        // Load actions
        for (auto& act : s["actions"]) {
            WaypointActionConfig a;
            a.switchToLinear = act.value("switchToLinear", false);
            a.switchToCircular = act.value("switchToCircular", false);
            a.radius = act.value("radius", 0.0f);
            a.angularSpeed = act.value("angularSpeed", 0.0f);
            a.clockwise = act.value("clockwise", true);
            cfg.actions.push_back(a);
        }
        std::string type = s["type"];
        if (type == "Linear") {
            cfg.motionType = SawbladeMotionType::Linear;
        } else if (type == "Circular") {
            cfg.motionType = SawbladeMotionType::Circular;
        }
        result.push_back(cfg);
    }

    return result;
}

bool JsonLoader::isGameCompleted() {
    fs::path filePath;
    if (Config::LOCAL_BUILD) {
        filePath = "../user_data/user_data.json";
    } else {
        filePath = "user_data/user_data.json";
    }


    if (!fs::exists(filePath)) return false;

    std::ifstream file(filePath);
    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof()) return false;

    json data;
    try {
        file >> data;
    } catch (...) {
        return false;
    }

    return data.value("gameCompleted", false);
}

void JsonLoader::setGameCompleted(bool completed) {
    fs::path filePath;
    if (Config::LOCAL_BUILD) {
        filePath = "../user_data/user_data.json";
    } else {
        filePath = "user_data/user_data.json";
    }

    json data;
    data["gameCompleted"] = completed;

    std::ofstream file(filePath, std::ios::trunc);
    if (file.is_open()) {
        file << data.dump(4);
    }
}
