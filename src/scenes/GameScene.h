#pragma once

#include <iostream>
#include <vector>

class GameObject;

enum {
    STILL = 0,
    RIGHT = 1,
    LEFT = 2
};

class GameScene {
protected:
    std::vector<std::string> texture_id_list;
    std::vector<GameObject *> game_objects;
    bool dead = false;
    int direction = STILL;

public:

    GameScene() = default;

    virtual ~GameScene() { std::cout << "Scene deleted!\n"; }

    virtual void Update() {}

    virtual void Draw() {}

    virtual void OnExit() {}

    virtual void OnEnter() {}

    virtual std::string GetStateID() { return ""; }

    std::vector<GameObject *> GetGameObjects() { return game_objects; }

    bool isDead() { return dead; }

    void ChangeDirection(int direct) { direction = direct; }

    int Direction() { return direction; }
};

