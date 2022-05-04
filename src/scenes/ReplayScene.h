#pragma once

#include "GameScene.h"
#include "../utils/LevelLoader.h"
#include <fstream>

class ReplayScene : public GameScene {
    static std::string ID;
    int player_y;
    std::ifstream data;

public:
    virtual ~ReplayScene() override {}

    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override { return ID; }
};