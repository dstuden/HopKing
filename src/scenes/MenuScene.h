#pragma once

#include "GameScene.h"
#include "../utils/TextureManager.h"
#include <vector>

class MenuScene : public GameScene {

    static std::string ID;
    std::vector<std::unique_ptr<GameObject>> game_objects;

public:
    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;
};