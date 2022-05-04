#pragma once

#include "../EntityObject.h"

class EndCheckpoint : public EntityObject {
    int texture_width;
    int texture_height;

public:
    EndCheckpoint(GameScene *parrent_scene, int x, int y, int width, int height, int texture_width, int texture_height,
          int animation_speed, int num_frames,
          std::string texture_ID);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;
};