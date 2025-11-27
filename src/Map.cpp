//
// Created by richa on 2025-09-09.
//

#include "Map.h"
#include "TextureManager.h"
#include <cmath>
#include <sstream>
#include <tinyxml2.h>


void Map::load(const char *path, SDL_Texture *ts) {

    tileset = ts;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path);

    auto* mapNode = doc.FirstChildElement("map");
    width = mapNode -> IntAttribute("width");
    height = mapNode -> IntAttribute("height");

//Fine

    auto* layer = mapNode->FirstChildElement("layer");

    auto* data = layer->FirstChildElement("data");

    std::string csv = data->GetText();

    std::stringstream ss(csv);

    tileData = std::vector(height, std::vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::string val;
            if (!std::getline(ss, val, ',')) break;
            tileData[i][j] = static_cast<int>(std::stoi(val));
        }
    }
 for (auto* objectGroup = mapNode->FirstChildElement("objectgroup");
     objectGroup != nullptr;
     objectGroup = objectGroup->NextSiblingElement("objectgroup")) {

    std::string groupName = objectGroup->Attribute("name");

    for (auto* obj = objectGroup->FirstChildElement("object");
         obj != nullptr;
         obj = obj->NextSiblingElement("object")) {

        Collider c;
        c.rect.x = obj->FloatAttribute("x");
        c.rect.y = obj->FloatAttribute("y");
        c.rect.w = obj->FloatAttribute("width");
        c.rect.h = obj->FloatAttribute("height");

        if (groupName == "Collision Layer") {
            colliders.push_back(c);
        }
        else if (groupName == "Item Layer" || groupName == "Object Layer 2") {
            SDL_FPoint spawn;
            spawn.x = obj->FloatAttribute("x");
            spawn.y = obj->FloatAttribute("y");
            itemSpawns.push_back(spawn);
        }
        else if (groupName == "Player Start") {
            SDL_FPoint spawn;
            spawn.x = obj->FloatAttribute("x");
            spawn.y = obj->FloatAttribute("y");
            playerSpawn = {spawn.x,spawn.y};
        }
        else if (groupName == "Next Level") {
            c.tag = "next_level";
            colliders.push_back(c);
        } else if (groupName == "Bullet Spawn") {
            SDL_FPoint spawn;
            spawn.x = obj->FloatAttribute("x");
            spawn.y = obj->FloatAttribute("y");
            bulletSpawnAreas.push_back({spawn.x,spawn.y});
        }
    }
}




}



void Map::draw(const Camera &cam) {
    SDL_FRect src{}, dest{};
    dest.w = dest.h = 32;


    int tilesetCols = 16;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int gid = tileData[row][col];

            if (gid == 0) continue; // empty tile, skip

            // Tiled firstgid usually starts at 1
            int tileIndex = gid - 1;

            // calculate source X/Y on the tileset
            src.x = (tileIndex % tilesetCols) * 32;
            src.y = (tileIndex / tilesetCols) * 32;
            src.w = 32;
            src.h = 32;

            // destination on screen
            dest.x = std::round(col * dest.w - cam.view.x);
            dest.y = std::round(row * dest.h - cam.view.y);

            TextureManager::draw(tileset, &src, &dest);
        }
    }

}