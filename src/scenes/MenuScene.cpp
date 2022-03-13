#include "MenuScene.h"

#include "../Engine.h"

std::string MenuScene::ID = "MENU";

void MenuScene::Update() {
    int max_size = game_objects.size();
    for (int i = 0; i < max_size;) {
        if (game_objects[i]->IsDead()) {
            game_objects[i]->Free();
            game_objects.erase(game_objects.begin() + i);
            max_size--; // not really necessary
        } else {
            game_objects[i]->Update();
            i++;
        }
    }
}

void MenuScene::Draw() {

}

void MenuScene::OnEnter() {
    game_objects.emplace_back(std::unique_ptr<GameObject>());

    TextureManager::Instance()->Load("../a", ID, Engine::Instance()->getRenderer());

}

void MenuScene::OnExit() {
    game_objects.clear();

    TextureManager::Instance()->Free();

}