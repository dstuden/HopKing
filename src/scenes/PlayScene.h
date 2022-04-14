#pragma once

#include "GameScene.h"
#include "../utils/TextureManager.h"
#include <vector>

class PlayScene : public GameScene {

    static std::string ID;

public:
    ~PlayScene() { std::cout << "Deleted Play Scene\n\n"; }

    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override;
};