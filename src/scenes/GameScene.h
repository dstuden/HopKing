#pragma once

#include <iostream>
#include <vector>

class GameObject;

class GameScene {
protected:
    std::vector<std::string> texture_id_list;
    std::vector<GameObject *> game_objects;
    bool dead = false;
    int pos_diff_x = 0;

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

    void MoveScene(int diff) { pos_diff_x = diff; }

    int ScenePos() { return pos_diff_x; }
};

