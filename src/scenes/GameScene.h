#pragma once

#include "../game-objects/EntityObject.h"
#include <string>
#include <vector>

class GameScene {
protected:
    std::vector<std::string> texture_id_list;
    std::vector<EntityObject *> game_objects;

public:

    GameScene() = default;

    ~GameScene() = default;

    virtual void Update() {}

    virtual void Draw() {}

    virtual void OnExit() {}

    virtual void OnEnter() {}

    virtual std::string GetStateID() { return ""; }

    std::vector<EntityObject *> GetGameObjects() { return game_objects; }
};

