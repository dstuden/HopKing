#pragma once

#include "GameScene.h"
#include "../utils/TextureManager.h"
#include "../game-objects/Entities.h"
#include <vector>

class MenuScene : public GameScene {

    static std::string ID;

public:
    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override;
};