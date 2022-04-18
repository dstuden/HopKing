#pragma once

#include "../utils/TextureManager.h"
#include "GameObject.h"
#include "../Engine.h"

class EntityObject : public GameObject {
protected:
    int lives = 0; // object is still alive at 0 lives
    bool invulnerable = false;
    uint32_t invulnerable_start;
    uint32_t invulnerability_duration = 1000; // 1 second

public:

    virtual ~EntityObject() override {
        std::cout<<"Removed Entity\n";
    }

    void Update() override {}

    void Draw() {
        TextureManager::Instance()->Draw(texture_ID, position.getX(), position.getY(), width, height,
                                         Engine::Instance()->getRenderer(), current_frame, SDL_FLIP_NONE);
    }

    void Free() override {
        collider.w = 0; // makes sure that other objects do not collide with this one before it gets destroyed
        collider.h = 0;
        collider.x = collider.y = -10000;

        dead = true;
    }

    void AddLife() {
        lives++;
    }

    bool isInvoulnerable() { return invulnerable; }

    virtual void Hit(uint32_t invulnerability_duration) override {}
    virtual void Hit() override {}

};

