#pragma once

#include "../EntityObject.h"
#include <iostream>

class PlayScene;

class Player : public EntityObject {
    bool jumping = false;
    bool falling = true;

    int points = 0;

    PlayScene *parrent_scene;

    Uint32 jump_start;
public:
    Player(PlayScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
           int num_frames, std::string texture_ID, int lives);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;

    void CheckCollision();

    bool isJumping() { return jumping; }

    bool isFalling() { return falling; }

    void AddPoints(int n) { points += n; }

    void SetPoints(int n) { points = n; }

    virtual void Hit(uint32_t invulnerability_duration) override {
        if (!isInvoulnerable()) {
            lives--;
            invulnerable = true;
            invulnerable_start = SDL_GetTicks();
        }
    }
};