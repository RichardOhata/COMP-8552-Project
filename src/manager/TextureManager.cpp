//
// Created by richa on 2025-09-09.
//

#include "TextureManager.h"
#include "../Game.h"

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


void TextureManager::loadLabel(Label& label) {
    auto it = textures.find(label.textureCacheKey);
    if (it != textures.end()) {
        label.texture = it->second;
        return;
    }
    updateLabel(label);
}

void TextureManager::updateLabel(Label& label) {

    if (!label.dirty) return;

    if (label.texture) {
        SDL_DestroyTexture(label.texture);
        label.texture = nullptr;
    }
    SDL_Surface* tempSurface = TTF_RenderText_Blended(
        label.font,
        label.text.c_str(),
        label.text.size(),
        label.color
        );
        if (!tempSurface) {
            std::cout << "Failed to load surface" << std::endl;
        }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, tempSurface);
    SDL_DestroySurface(tempSurface);

    if (!texture) {
        std::cerr << "Failed to create texture" << std::endl;
    }

    float w, h;
    SDL_GetTextureSize(texture, &w, &h);
    label.dst.w = w;
    label.dst.h = h;

    label.texture = texture;
    textures[label.textureCacheKey] = texture;
    label.dirty = false;
}

void TextureManager::draw(SDL_Texture* texture, const SDL_FRect* src, const SDL_FRect* dst) {
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    SDL_RenderTexture(game->renderer, texture, src, dst);
    // SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    // SDL_RenderRect(game->renderer, &dst);
    // SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Reset to black
}

void TextureManager::clean() {
    for (auto& tex : textures) {
        SDL_DestroyTexture(tex.second);
        tex.second = nullptr;
    }
    textures.clear();
}
