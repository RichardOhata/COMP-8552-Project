//
// Created by richa on 2025-09-09.
//

#ifndef TEST_GAMEOBJECT_H
#define TEST_GAMEOBJECT_H

#include "Game.h"

class GameObject {

    public:
    GameObject(const char* path, int x, int y);
    ~GameObject();

    void update(float deltaTime);
    void draw();

private:
    int xPos{}, yPos{};

    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect{}, destRect{};
};

#endif //TEST_GAMEOBJECT_H