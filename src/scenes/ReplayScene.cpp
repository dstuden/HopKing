#include "ReplayScene.h"
#include "../game-objects/Entities.h"
#include "SceneManager.h"

std::string ReplayScene::ID = "REPLAY";

void ReplayScene::Update() {
    if (!(data >> scene_controller_pos_diff_x >> player_y)) {
        data.close();
        remove("../tmp.txt");
        SceneManager::Instance()->PopScene();
    }

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

void ReplayScene::Draw() {
    for (auto &it: game_objects) {
        it->Draw();
    }

    TextureManager::Instance()->Draw("player", 484, player_y, 42, 54, Engine::Instance()->getRenderer(), 1,
                                     SDL_FLIP_NONE);
}

void ReplayScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/player.png", "player", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/animal.png", "animal", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/enemy.png", "enemy", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/platform1.png", "ground", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/background.png", "background", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/heart.png", "heart", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/block-small.png", "block-small", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/endcheckpoint.png", "endcheckpoint", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/block-big.png", "block-big", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/block-wide.png", "block-wide", Engine::Instance()->getRenderer());
    TextureManager::Instance()->Load("../assets/spike.png", "spike", Engine::Instance()->getRenderer());
    texture_id_list.push_back("player");
    texture_id_list.push_back("enemy");
    texture_id_list.push_back("animal");
    texture_id_list.push_back("endcheckpoint");
    texture_id_list.push_back("block-small");
    texture_id_list.push_back("block-big");
    texture_id_list.push_back("block-wide");
    texture_id_list.push_back("background");
    texture_id_list.push_back("heart");
    texture_id_list.push_back("spike");
    texture_id_list.push_back("ground");

    Background *background = new Background(
            this,
            -200,
            0,
            3840,
            1080,
            1,
            1,
            "background"
    );
    game_objects.push_back(background);

    std::ifstream level_data("../levels/levels.bin", std::ios::binary);
    Level tmp;
    while (level_data.read((char *) &tmp, sizeof(tmp))) {}

    LevelLoader::Instance()->LoadLevel(tmp, &game_objects, reinterpret_cast<PlayScene *>(this));

    level_data.close();

    data.open("../tmp.txt");
}

void ReplayScene::OnExit() {
    data.close();

    for (auto &it: game_objects) {
        it->Free();
        delete it;
    }
    game_objects.clear();

    for (auto &it: texture_id_list) {
        TextureManager::Instance()->FreeFromTextureMap(it);
    }
}