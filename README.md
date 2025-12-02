# Reflex

[itch.io](https://orange8846.itch.io/reflex)

A 2D Top-Down Maze/Avoidance game built with SDL3, C++, CLion, Tiled, for COMP 8552

Game involves precise movement and timings where your objective to navigate through hazard-filled levels and parrying incoming projectiles, all while collect coins in order to progress.

## How to Install
1. Install release build 
<img width="1279" height="674" alt="image" src="https://github.com/user-attachments/assets/e9f85d07-f1b4-40fe-8579-35478f876a0e" />

<img width="1230" height="467" alt="image" src="https://github.com/user-attachments/assets/3f63233c-fff3-432a-afbe-3d5dc38be873" />

2. Unzip downloadable folder

3. Run `Reflex.exe`


## Controls
- Move: WASD
- Parry: F
- Show Debug Colliders: C
- Return to Main Menu: ESC

## Features
- Precise platforming movement
- Parry system that reflects incoming projectiles
- Dynamic hazards
- One-hit death system
- Multi-stage level loading built with Tiled maps
- Custom ECS architecture

## Engine Overview

Reflex was built using a custom 2D game engine written in C++ using SDL3.
The engine follows an Entity-Component-System (ECS) architecture, where gameplay objects are implemented as entities in different parts of the game (e.g. sawblades, player, scenestate, UI elements, etc.) and are composed of modular componenets, which the system will all handle.

### Relevant Engine Systems:
- Animation System
- Collision System
- SawBlade Movement System
- Render System
- Movement System
- Parry System
- UI Renderer System
- Collider Debug System

### Level & Asset Pipeline

Level design entities are loaded in dynamically using custom Tiled Maps which include:
- Player Start Postion
- Colliders
- Coin Spawns
- Bullet/Projectile Spawners
- Goal Detection

Sawblade & Bullet/Projectiles data were loading using JSON.

Sprites, textures, animations, were loaded in with their respective class managers (Texture Manager, Asset Manager, JsonLoader).
