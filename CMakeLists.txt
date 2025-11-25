cmake_minimum_required(VERSION 4.0)
project(Test)

set(CMAKE_CXX_STANDARD 20)

#Set SDL3 include and lib paths

if (WIN32)
    set(SDL3_PATH "C:/Users/richa/Downloads/sdl3")
    set(SDL3_IMAGE_PATH "C:/Users/richa/Downloads/sdl3_image")
    include_directories(
            ${SDL3_PATH}/include
            ${SDL3_IMAGE_PATH}/include
            ${PROJECT_SOURCE_DIR}/src
            ${PROJECT_SOURCE_DIR}/src/utils
            ${PROJECT_SOURCE_DIR}/src/ecs
            ${PROJECT_SOURCE_DIR}/src/ecs/system
            ${PROJECT_SOURCE_DIR}/src/vendor
    )
    link_directories(
            ${SDL3_PATH}/lib
            ${SDL3_IMAGE_PATH}/lib
    )
endif()
add_executable(Test
        src/main.cpp
#        src/Game.h
        src/Game.cpp
#        src/TextureManager.h
        src/TextureManager.cpp
        src/Map.cpp
        src/GameObject.cpp
#        src/ecs/ComponentType.h
#        src/ecs/Entity.h
#        src/ecs/Component.h
#        src/ecs/system/MovementSystem.h
#        src/ecs/system/RenderSystem.h
#        src/ecs/World.h
#        src/Vector2D.h
#        src/ecs/system/KeyboardInputSystem.h
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
)

#if (MSVC)
#    target_link_libraries(Test SDL3.lib)
#else()
    target_link_libraries(Test
            SDL3
            SDL3_image
    )
#endif()