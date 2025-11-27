//
// Created by richa on 2025-09-09.
//

#include "GameObject.h"

#include <time.h>

#include "TextureManager.h"

GameObject::GameObject(const char *path, int x, int y) :
xPos(x), yPos(y), texture(TextureManager::load(path))
{

}

GameObject::~GameObject() {
    if (texture) SDL_DestroyTexture(texture);
}

void GameObject::update(float deltaTime) {
    // Speed in units per second
    float speed = 100.0f;

    // Move GameObject on x and y each frame based on deltaTime
    xPos += static_cast<int>(speed * deltaTime);
    yPos += static_cast<int>(speed * deltaTime);

    srcRect.x = srcRect.y = 0;
    srcRect.w = srcRect.h = 32;

    destRect.x = static_cast<float>(xPos);
    destRect.y = static_cast<float>(yPos);
    destRect.w = static_cast<float>(srcRect.w);
    destRect.h = static_cast<float>(srcRect.h);
}


void GameObject::draw() {
    TextureManager::draw(texture, &srcRect, &destRect);
}
