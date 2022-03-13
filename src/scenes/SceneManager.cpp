#include "SceneManager.h"

SceneManager *SceneManager::instance = NULL;

void SceneManager::ChangeScene(GameScene scene) {
    if (!game_scenes->empty()) {
        game_scenes->back()->OnExit();
        delete game_scenes->back();
    }

    PushScene(scene);
    game_scenes->back()->OnEnter();
}

void SceneManager::CleanScenes() {

}

void SceneManager::PopScene() {

}

void SceneManager::PushScene(GameScene scene) {

}
