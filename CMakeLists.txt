cmake_minimum_required(VERSION 3.21)
project(HopKing)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp src/Engine.cpp src/Engine.h src/utils/InputManager.cpp src/utils/InputManager.h src/utils/TextureManager.cpp src/utils/TextureManager.h src/game-objects/EntityObject.h src/scenes/GameScene.h src/utils/Vector2D.cpp src/utils/Vector2D.h src/scenes/SceneManager.cpp src/scenes/SceneManager.h src/scenes/PlayScene.cpp src/scenes/PlayScene.h src/game-objects/entities/Player.cpp src/game-objects/entities/Player.h src/game-objects/entities/Button.cpp src/game-objects/entities/Button.h src/game-objects/entities/Enemy.cpp src/game-objects/entities/Enemy.h src/game-objects/GameObject.h src/game-objects/entities/Platform.cpp src/game-objects/entities/Platform.h src/game-objects/Entities.h src/game-objects/entities/Background.cpp src/game-objects/entities/Background.h src/scenes/MenuScene.cpp src/scenes/MenuScene.h src/game-objects/entities/AnimatedSprite.cpp src/game-objects/entities/AnimatedSprite.h src/scenes/PlaySelectScene.cpp src/scenes/PlaySelectScene.h src/game-objects/entities/Spike.cpp src/game-objects/entities/Spike.h src/game-objects/entities/Animal.cpp src/game-objects/entities/Animal.h src/game-objects/entities/EndCheckpoint.cpp src/game-objects/entities/EndCheckpoint.h src/game-objects/entities/HealthUp.cpp src/game-objects/entities/HealthUp.h src/scenes/EscapeMenuScene.cpp src/scenes/EscapeMenuScene.h src/scenes/GameOverScene.cpp src/scenes/GameOverScene.h src/utils/LevelLoader.cpp src/utils/LevelLoader.h src/scenes/GameEndScene.cpp src/scenes/GameEndScene.h src/scenes/ReplayScene.cpp src/scenes/ReplayScene.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
