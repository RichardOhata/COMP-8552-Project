//
// Created by richa on 2025-11-18.
//


#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Vector2D.h"
#include "nlohmann/json.hpp"  // header-only JSON library
#include "LevelData.h"

class LevelLoader {
public:
    static LevelData load(const std::string& path) {
        LevelData data;
        std::ifstream file(path);
        if (!file.is_open()) return data;

        nlohmann::json j;
        file >> j;

        data.player.x = j["player"]["x"];
        data.player.y = j["player"]["y"];

        for (auto& c : j["coins"])
            data.coins.push_back({c["x"], c["y"]});

        for (auto& s : j["sawblades"]) {
            data.sawblades.push_back({
                {s["pointA"][0], s["pointA"][1]},
                {s["pointB"][0], s["pointB"][1]},
                s["speed"],
                s["scale"],
                s["stationary"]
            });
        }

        return data;
    }
};
