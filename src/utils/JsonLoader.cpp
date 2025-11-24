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
        std::string motion = s["type"];
        cfg.motionType = (motion == "linear") ? SawbladeMotionType::Linear : SawbladeMotionType::Circular;
        if (cfg.motionType == SawbladeMotionType::Circular) {
            cfg.center = { s["center"][0], s["center"][1] };
            cfg.radius = s["radius"];
            cfg.angularSpeed = s["angularSpeed"];
            cfg.angle = s.value("angle", 0.0f);
            cfg.scale = s["scale"];
            cfg.clockwise = s.value("clockwise", false);
        } else {
            cfg.pointA = { s["pointA"][0], s["pointA"][1] };
            cfg.pointB = { s["pointB"][0], s["pointB"][1] };
            cfg.speed = s["speed"];
            cfg.scale = s["scale"];
            cfg.stationary = s["stationary"];
        }

        result.push_back(cfg);
    }

    return result;
}