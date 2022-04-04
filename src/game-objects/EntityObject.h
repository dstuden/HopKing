#pragma once

#include "../utils/TextureManager.h"
#include "GameObject.h"
#include "../Engine.h"

class EntityObject : public GameObject {
protected:
    int lives = 0; // object is still alive at 0 lives
    bool invulnerable = false;
    uint32_t invulnerable_start;

public:

    void Update() override {}

    void Draw() {
        TextureManager::Instance()->Draw(texture_ID, position.getX(), position.getY(), width, height,
                                         Engine::Instance()->getRenderer(), current_frame, SDL_FLIP_NONE);
    }

    virtual bool IsDead() {
        return dead;
    }

    void Free() override {
        dead = true;
    }

    void AddLife() {
        lives++;
    }

};

