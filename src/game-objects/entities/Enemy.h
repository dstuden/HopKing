#pragma once

#include "../EntityObject.h"
#include <iostream>

class Enemy : public EntityObject {
    bool falling = true;
    bool direction = false; // right = false, left = true
public:
    Enemy(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
          int num_frames, std::string texture_ID, int lives);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;

    void CheckCollision();

    bool isFalling() { return falling; }

    virtual void Hit() override {
        if (!isInvoulnerable()) {
            lives--;
            invulnerable = true;
            invulnerable_start = SDL_GetTicks();
        }
    }
};