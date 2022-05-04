#pragma once

#include "GameScene.h"
#include <vector>

class SceneManager {
    std::vector<GameScene *> game_scenes;

    static SceneManager *instance;

    SceneManager() = default;

public:

    static SceneManager *Instance() {
        if (!instance)
            instance = new SceneManager;

        return instance;
    }

    void PopScene();

    void PushScene(GameScene *scene);

    void CleanScenes();

    void Update();

    void Render();

    void KillBack() { game_scenes.back()->Die(); }
};