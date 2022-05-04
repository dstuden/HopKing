#pragma once

#include "GameScene.h"
#include <SDL2/SDL_ttf.h>
#include <map>

class Button;

class MenuScene : public GameScene {
    static std::string ID;

    std::vector<Button *> buttons;

    TTF_Font *title_font;
    SDL_Color title_color;
    SDL_Surface *surface;
    SDL_Texture *texture;

public:

    virtual ~MenuScene() override {}

    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    std::string GetStateID() override;
};

