cmake_minimum_required(VERSION 4.0)
project(Test)

set(CMAKE_CXX_STANDARD 20)

#Set SDL3 include and lib paths

if (WIN32)
    set(SDL3_PATH "./dev/sdl3 3.3.2")
    set(SDL3_IMAGE_PATH "./dev/sdl3_image")
    set(SDL3_TTF_PATH "./dev/sdl3_ttf")
    set(SDL3_MIXER_PATH "./dev/sdl3_mixer 3.1.0")
    include_directories(
            ${SDL3_PATH}/include
            ${SDL3_IMAGE_PATH}/include
            ${SDL3_TTF_PATH}/include
            ${SDL3_MIXER_PATH}/include
            ${PROJECT_SOURCE_DIR}/src
            ${PROJECT_SOURCE_DIR}/src/utils
            ${PROJECT_SOURCE_DIR}/src/ecs
            ${PROJECT_SOURCE_DIR}/src/ecs/system
            ${PROJECT_SOURCE_DIR}/src/vendor
    )
    link_directories(
            ${SDL3_PATH}/lib
            ${SDL3_IMAGE_PATH}/lib
            ${SDL3_TTF_PATH}/lib
            ${SDL3_MIXER_PATH}/lib
    )
endif()
add_executable(Test
        src/main.cpp
        src/Game.cpp
        src/TextureManager.cpp
        src/Map.cpp
        src/GameObject.cpp
        src/utils/Vector2D.cpp
        src/utils/Collision.cpp
        src/ecs/system/CollisionSystem.cpp
        src/World.cpp
        src/vendor/tinyxml2.cpp
        src/manager/AssetManager.cpp
        src/manager/Scene.cpp
        src/utils/JsonLoader.cpp
        src/vendor/json.hpp
        src/ecs/system/MouseInputSystem.cpp
        src/manager/MainMenuScene.cpp
        src/manager/AudioManager.cpp
)


    target_link_libraries(Test
            SDL3
            SDL3_image
            SDL3_ttf
            SDL3_mixer
    )