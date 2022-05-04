#pragma once

#include "../EntityObject.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

class Button : public GameObject {
    bool selected = false;

    void (*callback)();

    TTF_Font *font;
    SDL_Color text_color;
    SDL_Surface *surface;
    SDL_Texture *texture;

public:
    Button(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
           int num_frames, std::string texture_ID, void (*function)(), std::string display_text);

    virtual ~Button() override {
        std::cout << "Removed Button\n";
    }

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;

    void Select() { selected = true; }

    void Deselect() { selected = false; }
};