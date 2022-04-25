#include "PlayScene.h"
#include "../game-objects/Entities.h"
#include "../Engine.h"

std::string PlayScene::ID = "PLAY";

void PlayScene::Update() {
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

void PlayScene::Draw() {
    for (auto &it: game_objects) {
        it->Draw();
    }
    for (int i = 0; i < controller_lives; i++) {
        TextureManager::Instance()->Draw(
                "heart",
                10+70*i,
                10,
                64,
                64,
                Engine::Instance()->getRenderer(),
                0,
                SDL_FLIP_NONE
        );
    }
}

void PlayScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/player.png", "player", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/platform1.png", "platform1", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/background.png", "background", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/heart.png", "heart", Engine::Instance()->getRenderer());
    texture_id_list.push_back("player");
    texture_id_list.push_back("background");
    texture_id_list.push_back("heart");
    texture_id_list.push_back("platform1");

    Player *player1 = new Player(
            this,
            (Engine::Instance()->WindowSize().w / 2) - 32,
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
            100,
            200,
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
            800,
            20000,
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

    Background *background = new Background(
            this,
            -100,
            0,
            3840,
            1080,
            1,
            1,
            "background"
    );

    controller_lives = player1->GetLives();

    game_objects.push_back(background);
    game_objects.push_back(platform1);
    game_objects.push_back(platform2);
    game_objects.push_back(enemy1);
    game_objects.push_back(player1);

    std::cout << "Entered menu!\n\n";
}

void PlayScene::OnExit() {
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

std::string PlayScene::GetStateID() { return ID; }