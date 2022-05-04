#pragma once

#include "../EntityObject.h"
#include <iostream>

class PlayScene;

class Animal : public EntityObject {
    PlayScene *parrent_scene;
public:
    Animal(PlayScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
          int num_frames, std::string texture_ID);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;
};