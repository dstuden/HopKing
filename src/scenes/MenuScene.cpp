#include "MenuScene.h"

#include "../Engine.h"

std::string MenuScene::ID = "MENU";

void MenuScene::Update() {
    int max_size = game_objects.size();
    for (int i = 0; i < max_size;) {
        if (game_objects[i]->IsDead()) {
            game_objects[i]->Free();
            delete game_objects[i];
            game_objects.erase(game_objects.begin() + i);
            max_size--; // not really necessary
        } else {
            game_objects[i]->Update();
            i++;
        }
    }
}

void MenuScene::Draw() {
    for (auto &it: game_objects) {
        it->Draw();
    }
}

void MenuScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/player.png", "player", Engine::Instance()->getRenderer());
    texture_id_list.push_back("player");

    Player *player = new Player(
            this,
            100,
            300,
            64,
            64,
            500,
            2,
            "player",
            3
    );

    Enemy *enemy = new Enemy(
            this,
            100,
            600,
            64,
            64,
            1,
            2,
            "player",
            3
    );

    Enemy *enemy2 = new Enemy(
            this,
            400,
            600,
            64,
            64,
            1,
            2,
            "player",
            3
    );
    Enemy *enemy3 = new Enemy(
            this,
            600,
            600,
            64,
            64,
            1,
            2,
            "player",
            3
    );


    game_objects.push_back(player);
    game_objects.push_back(enemy);
    game_objects.push_back(enemy2);
    game_objects.push_back(enemy3);

    std::cout << "Entered menu!\n\n";
}

void MenuScene::OnExit() {
    for (int i = 0; i <= game_objects.size(); i++) {
        game_objects.back()->Free();
        delete game_objects.back();
        game_objects.pop_back();
    }

    for(auto &it : texture_id_list)
        TextureManager::Instance()->FreeFromTextureMap(it);

}

std::string MenuScene::GetStateID() { return ID; }