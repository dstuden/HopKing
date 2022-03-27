#pragma once

#include "../GameObject.h"
#include <iostream>

class Button : public GameObject {
    bool selected = false;
public:
    Button(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
           int num_frames, std::string texture_ID);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;
};