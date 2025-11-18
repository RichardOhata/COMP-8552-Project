//
// Created by richa on 2025-11-18.
//

#ifndef TEST_LEVELDATA_H
#define TEST_LEVELDATA_H
#pragma once
#include "Vector2D.h"
#include <vector>

struct CoinData { float x, y; };
struct SawbladeData { Vector2D pointA, pointB; float speed; float scale; bool stationary; };
struct PlayerData { float x, y; };
struct LevelData {
    PlayerData player;
    std::vector<CoinData> coins;
    std::vector<SawbladeData> sawblades;
};

#endif //TEST_LEVELDATA_H