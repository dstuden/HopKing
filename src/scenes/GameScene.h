#pragma once

#include "../game-objects/GameObject.h"
#include <string>
#include <vector>

class GameScene {
protected:
    std::vector<std::string> texture_id_list;
    std::vector<GameObject *> game_objects;

public:

    GameScene() = default;

    ~GameScene() = default;

    virtual void Update() {}

    virtual void Draw() {}

    virtual void OnExit() {}

    virtual void OnEnter() {}

    virtual std::string GetStateID() { return ""; }

    std::vector<GameObject *> GetGameObjects() { return game_objects; }
};

