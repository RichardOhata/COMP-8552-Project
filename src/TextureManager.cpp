//
// Created by richa on 2025-09-09.
//

#include "TextureManager.h"
#include "Game.h"

#include <iostream>
#include <ostream>

// Grabs the reference of the object
extern Game* game;
std::unordered_map<std::string, SDL_Texture*> TextureManager::textures;
SDL_Texture* TextureManager::load(const char* path) {

    // Check if texture already exists in map
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second;
    }
    //a surface represents an image in ram (cpu memory)

    SDL_Surface* tempSurface = IMG_Load(path);
    if (!tempSurface) {
        std::cout << "Failed to load image" << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, tempSurface);

    //clean up
    SDL_DestroySurface(tempSurface);


    if (!texture) {
        std::cout << "Failed to create texture texture" << std::endl;
        return nullptr;
    }
    textures[path] = texture;
    return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_FRect src, SDL_FRect dst) {

    SDL_RenderTexture(game->renderer, texture, &src, &dst);

}

void TextureManager::clean() {
    for (auto& tex : textures) {
        SDL_DestroyTexture(tex.second);
        tex.second = nullptr;
    }
    textures.clear();
}
