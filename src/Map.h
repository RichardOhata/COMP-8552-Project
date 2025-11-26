//
// Created by richa on 2025-09-09.
//

#ifndef TEST_MAP_H
#define TEST_MAP_H

#include <vector>
#include <SDL3/SDL.h>

#include <Component.h>
class Map {
public:
    Map() = default;
    ~Map() = default;

    void load(const char *path, SDL_Texture *ts);
    void draw(const Camera &cam);

    SDL_Texture *tileset = nullptr;
    int width{}, height{};
    std::vector<std::vector<int>> tileData;
    std::vector<Collider> colliders;
    std::vector<SDL_FPoint> itemSpawns;
    Vector2D playerSpawn{};
    Collider nextAreaZone;
    std::vector<Vector2D> bulletSpawnAreas{};
};

#endif //TEST_MAP_H