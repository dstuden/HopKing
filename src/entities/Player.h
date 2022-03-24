#pragma once

#include "GameObject.h"
#include <iostream>

class Player : public GameObject {
    int lives;

    bool invulnerable = false;
    uint32_t invulnerable_start;

public:
    Player(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
           int num_frames, std::string texture_ID, int lives);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;

    void AddLife();

    bool CheckCollision(GameScene *parrent);

    bool IsInVoulnerable() { return invulnerable; }

    void Invoulnerable() { invulnerable = true; }

    void EnemyHit() {
        if (!invulnerable) {
            lives--;
            invulnerable = true;
        }
    }
};