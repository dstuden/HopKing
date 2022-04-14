#include "SceneManager.h"

SceneManager *SceneManager::instance = NULL;

void SceneManager::ChangeScene(GameScene *scene) {
    PopScene();
    PushScene(scene);
    game_scenes.back()->OnEnter();
}

void SceneManager::CleanScenes() {
    if (!game_scenes.empty()) {
        for (auto &it: game_scenes) {
            it->OnExit();
            delete it;
        }
        game_scenes.clear();
    }
}

void SceneManager::PopScene() {
    if (!game_scenes.empty()) {
        game_scenes.back()->OnExit();
        delete game_scenes.back();
        game_scenes.pop_back();
    }
}

void SceneManager::PushScene(GameScene *scene) {
    game_scenes.push_back(scene);
    game_scenes.back()->OnEnter();
}

void SceneManager::Update() {
    if (!game_scenes.empty()) {
        if (game_scenes.back()->isDead())
        {
            delete game_scenes.back();
            game_scenes.pop_back();
        }
        else
            game_scenes.back()->Update();
    }
}

void SceneManager::Render() {
    if (!game_scenes.empty())
        game_scenes.back()->Draw();
}

