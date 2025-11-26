//
// Created by richa on 2025-11-23.
//

#include "JsonLoader.h"
#include <fstream>
#include <iostream>
#include "vendor/json.hpp"
// #include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<SawbladeConfig> JsonLoader::loadSawblades(const std::string& sceneName)
{
    std::vector<SawbladeConfig> result;


    std::string filePath = "C:/Users/richa/Desktop/COMP-8552-Project/src/level_data/" + sceneName + ".json";;
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