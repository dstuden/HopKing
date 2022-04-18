#pragma once

#include "../EntityObject.h"

class Platform : public EntityObject {
    bool moving = false;
    int moveX = 0;
    int moveY = 0;

public:
    Platform(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed, int num_frames,
             std::string texture_ID);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;

    void CheckCollision();
};