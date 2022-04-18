#include "MenuScene.h"
#include "../game-objects/Entities.h"
#include "../Engine.h"

std::string MenuScene::ID = "MENU";

int num_of_buttons = 0;

void MenuScene::Update() {
    static int button = 0;

// need to check for release of a key...
//    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_DOWN) && button < num_of_buttons - 1)
//        button++;
//    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_UP) && button > 0)
//        button--;

    int max_size = game_objects.size();
    for (int i = 0; i < max_size;) {
        if (game_objects[i]->IsDead()) {
            game_objects[i]->Free();
            delete game_objects[i];
            game_objects.erase(game_objects.begin() + i);
            max_size--;
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
    TextureManager::Instance()->Load("../assets/platform1.png", "platform1", Engine::Instance()->getRenderer());
    texture_id_list.push_back("player");
    texture_id_list.push_back("platform1");

    Player *player1 = new Player(
            this,
            400,
            300,
            32,
            64,
            1,
            1,
            "player",
            3
    );

    Enemy *enemy1 = new Enemy(
            this,
            300,
            300,
            32,
            64,
            1,
            1,
            "player",
            2
    );

    Platform *platform1 = new Platform(
            this,
            0,
            600,
            1984,
            64,
            1,
            1,
            "platform1"
    );

    Platform *platform2 = new Platform(
            this,
            400,
            400,
            64,
            128,
            1,
            1,
            "platform1"
    );
    game_objects.push_back(player1);
    game_objects.push_back(platform1);
    game_objects.push_back(platform2);
    game_objects.push_back(enemy1);

    for (auto &it: game_objects)
        if (it->GetObjectID() == "Button")
            num_of_buttons++;

    std::cout << "Entered menu!\n\n";
}

void MenuScene::OnExit() {
    for (auto &it: game_objects) {
        it->Free();
        delete it;
    }
    game_objects.clear();

    for (auto &it: texture_id_list) {
        TextureManager::Instance()->FreeFromTextureMap(it);
    }

    dead = true;
}

std::string MenuScene::GetStateID() { return ID; }