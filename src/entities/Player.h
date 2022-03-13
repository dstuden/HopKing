#pragma once

#include "GameObject.h"

class Player : public GameObject {
public:
    Player(GameScene *parrent_scene, int x, int y, int texture_width, int texture_height, int animation_speed,
           int num_frames);

    ~Player() = default;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;
};