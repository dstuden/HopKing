#include "../utils/Vector2D.h"
#include <SDL2/SDL.h>
#include <iostream>

class GameScene;

class GameObject {

protected:
    GameScene *parrent_scene;

    Vector2D velocity;
    Vector2D position;

    int width;
    int height;

    SDL_Rect collider;

    Uint32 ID;
    std::string object_ID;

    int animation_speed = 1;
    int num_frames = 1;
    int current_frame = 0;

    std::string texture_ID;

    bool dead = false;

public:

    GameObject() {
        static int getID = 0;
        ID = getID++;
    }

    virtual ~GameObject() = default;

    virtual void Update() = 0;

    virtual void Draw() = 0;

    int GetID() { return ID; }

    std::string GetObjectID() { return object_ID; }

    virtual SDL_Rect *GetRect() { return &collider; }

    Vector2D GetPosition() { return position; }

    Vector2D GetVelocity() { return velocity; }

    virtual void Hit() {}

    virtual void Hit(uint32_t invulnerability_duration) {}

    virtual void Free() = 0;

    virtual bool IsDead() {
        return dead;
    }
};