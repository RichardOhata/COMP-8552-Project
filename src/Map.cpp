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
            tileData[i][j] = std::stoi(val);
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

        // switch (groupName) {
        //     case "Collision Layer":
        // }
        if (groupName == "Collision Layer") {
            colliders.push_back(c);
        }
        else if (groupName == "Item Layer" || groupName == "Object Layer 2") {
            SDL_FPoint spawn;
            spawn.x = obj->FloatAttribute("x");
            spawn.y = obj->FloatAttribute("y");
            itemSpawns.push_back(spawn);
        }
        else if (groupName == "Enemy Layer") {

        }
    }
}




}



void Map::draw(const Camera &cam) {

    SDL_FRect src{}, dest{};

    dest.w = dest.h = 32;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int type = tileData[row][col];

            float worldX = static_cast<float>(col) * dest.w;
            float worldY = static_cast<float>(row) * dest.h;
            dest.x = std::round(worldX - cam.view.x);
            dest.y = std::round(worldY - cam.view.y);

            switch (type) {
                case 1:
                    // dirt
                    src.x = 0;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 2:
                    // /grass
                    src.x = 32;
                    src.y = 0;
                    src.w = 32;
                    src.h = 32;
                    break;
                case 4:
                    // water
                    src.x = 32;
                    src.y = 32;
                    src.w = 32;
                    src.h = 32;
                    break;
                default:
                    break;
            }
            TextureManager::draw(tileset, src, dest);
        }
    }
}