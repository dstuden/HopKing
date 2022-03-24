cmake_minimum_required(VERSION 3.21)
project(HopKing)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp src/Engine.cpp src/Engine.h src/utils/InputManager.cpp src/utils/InputManager.h src/utils/TextureManager.cpp src/utils/TextureManager.h src/entities/GameObject.h src/scenes/GameScene.h src/utils/Vector2D.cpp src/utils/Vector2D.h src/scenes/SceneManager.cpp src/scenes/SceneManager.h src/scenes/MenuScene.cpp src/scenes/MenuScene.h src/entities/Player.cpp src/entities/Player.h src/entities/Button.cpp src/entities/Button.h src/entities/Entities.h src/scenes/Scenes.h src/entities/Enemy.cpp src/entities/Enemy.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
