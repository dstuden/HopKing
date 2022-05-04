#pragma once

#include <vector>
#include "GameScene.h"
#include "../game-objects/entities/Button.h"

struct PlayerSave {
    char player_name[6];
    int level;
    int points;
    int lives;
};

class GameOverScene : public GameScene {
    static std::string ID;

    TTF_Font *title_font;
    SDL_Color title_color;
    SDL_Surface *surface;
    SDL_Texture *texture;

    PlayerSave player;

    std::vector<Button *> buttons;

public:
    GameOverScene(PlayerSave player) {
        this->player = player;
    }

    virtual ~GameOverScene() override {}

    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override;
};