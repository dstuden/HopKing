#pragma once

#include <vector>
#include "GameScene.h"
#include "../game-objects/entities/Button.h"
#include <SDL2/SDL_ttf.h>

class PlaySelectScene : public GameScene {
    static std::string ID;

    bool player_selected = false;
    std::string player_name = "";
    bool save_found = false;

    std::vector<Button *> buttons;

    TTF_Font *title_font;
    TTF_Font *player_name_render;

    SDL_Color title_color;
    SDL_Color player_name_color;

public:
    virtual ~PlaySelectScene() override {}

    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override;
};