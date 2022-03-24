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

    void ChangeScene(GameScene *scene);

    void PushScene(GameScene *scene);

    void CleanScenes();

    void Update();

    void Render();
};