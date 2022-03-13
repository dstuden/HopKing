#pragma once

#include "../entities/GameObject.h"
#include <string>
#include <memory>

class GameScene {
public:

    GameScene() = default;

    ~GameScene() = default;

    virtual void Update() {}

    virtual void Draw() {}

    virtual void OnExit() {}

    virtual void OnEnter() {}
};

