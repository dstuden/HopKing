#pragma once

#include "GameScene.h"

class MenuScene : public GameScene {
    static std::string ID;
public:
    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override;
};

