#pragma once

#include <vector>
#include "GameScene.h"
#include "../game-objects/entities/Button.h"

class EscapeMenuScene : public GameScene {
    static std::string ID;

    std::string player_name;
    int points;
    int level;
    int lives;

    std::vector<Button *> buttons;

public:
    EscapeMenuScene(std::string name, int level, int points, int lives) {
        this->level = level;
        this->player_name = name;
        this->points = points;
        this->lives = lives;
    }

    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override;
};