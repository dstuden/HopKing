#pragma once

#include "../EntityObject.h"

class Spike : public EntityObject {
    int texture_width;
    int texture_height;

public:
    Spike(GameScene *parrent_scene, int x, int y, int width, int height, int texture_width, int texture_height,
             int animation_speed, int num_frames,
             std::string texture_ID);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;
};