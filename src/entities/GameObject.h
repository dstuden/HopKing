#pragma once

#include "../utils/Vector2D.h"

class GameScene;

class GameObject {
protected:
    GameScene *parrent_scene;

    Vector2D velocity;
    Vector2D position;

    int texture_width;
    int texture_height;

    int animation_speed;
    int num_frames;

    bool dead;

public:
    GameObject() = default;

    ~GameObject() = default;

    virtual void Update() = 0;

    virtual void Draw() = 0;

    virtual bool IsDead() {
        return dead;
    }

    virtual void Free() = 0;
};

