#pragma once

#include <vector>
#include "GameScene.h"
#include "../game-objects/entities/Button.h"
#include <SDL2/SDL_ttf.h>

class GameEndScene : public GameScene {
    static std::string ID;

    bool show_results = false;
    std::string player_name = "";

    std::vector<Button *> buttons;

    TTF_Font *title_font;
    SDL_Color title_color;
    SDL_Surface *title_surface;
    SDL_Texture *title_texture;
    SDL_Rect title_dest;

    std::string scoreboard = "";

public:
    virtual ~GameEndScene() override {}

    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override;
};