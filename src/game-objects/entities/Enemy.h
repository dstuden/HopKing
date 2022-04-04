#pragma once

#include "../EntityObject.h"
#include <iostream>

class Enemy : public EntityObject {
    int lives;

    bool invulnerable = false;
    uint32_t invulnerable_start;

public:
    Enemy(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
           int num_frames, std::string texture_ID, int lives);

    virtual void Update() override;

    virtual void Draw() override;

    virtual void Free() override;

    void CheckCollision();

    bool IsInVoulnerable() const { return invulnerable; }

    void Invoulnerable() { invulnerable = true; }

    void EnemyHit() {
        if (!invulnerable) {
            lives--;
            invulnerable = true;
        }
    }
};