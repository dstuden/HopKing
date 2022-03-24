#pragma once

#include "../utils/Vector2D.h"
#include <SDL2/SDL.h>
#include <iostream>

class GameScene;

class GameObject {
protected:
    GameScene *parrent_scene;

    Vector2D velocity;
    Vector2D position;

    int width;
    int height;

    SDL_Rect
            src_rect,
            dest_rect;

    int animation_speed = 1;
    int num_frames = 1;
    int current_frame = 0;

    std::string texture_ID;

    bool dead = false;

    Uint32 ID;

public:
    GameObject() {
        static int getID = 0;
        ID = getID++;
    }

    ~GameObject() {
        std::cout << "Destroyed game object!\n";
    }

    virtual void Update() = 0;

    virtual void Draw() = 0;

    virtual bool IsDead() {
        return dead;
    }

    int GetID() { return ID; }

    virtual SDL_Rect *GetRect() { return &dest_rect; }

    virtual void Free() = 0;
};

