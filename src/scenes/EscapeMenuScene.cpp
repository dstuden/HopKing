#include "EscapeMenuScene.h"
#include <SDL2/SDL.h>
#include "../Engine.h"
#include "../utils/InputManager.h"
#include "SceneManager.h"
#include <fstream>
#include <cstring>

std::string EscapeMenuScene::ID = "MENUSELECT";

struct PlayerSave {
    char player_name[6];
    int level;
    int points;
    int lives;
};

int player_points;
std::string p_name;
int player_level;
int player_lives;

void save() {
    PlayerSave tmp;

    std::ifstream read_data("../player-saves/saves.bin", std::ios::binary);
    std::ofstream write_data("../player-saves/saves-tmp.bin", std::ios::binary);

    if (read_data.is_open() && write_data.is_open()) {
        while (read_data.read((char *) &tmp, sizeof(tmp))) {
            if (strcmp(tmp.player_name, p_name.c_str()) != 0) {
                write_data.write((char *) &tmp, sizeof(tmp));
            }
        }

        strcpy(tmp.player_name, p_name.c_str());
        tmp.level = player_level;
        tmp.points = player_points;
        tmp.lives = player_lives;

        write_data.write((char *) &tmp, sizeof(tmp));

        read_data.close();
        write_data.close();

        remove("../player-saves/saves.bin");
        rename("../player-saves/saves-tmp.bin", "../player-saves/saves.bin");
    }
}

void quit() {
    Engine::Instance()->Kill();
}

void EscapeMenuScene::Update() {
    static int i = 0;
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_UP))
        if (i - 1 >= 0) i--;
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_DOWN))
        if (i + 1 < buttons.size()) i++;

    int n = 0;
    for (auto &it: buttons) {
        if (n == i) it->Select();
        else it->Deselect();
        it->Update();
        n++;
    }
}


void EscapeMenuScene::Draw() {
    for (auto &it: buttons) {
        it->Draw();
    }
}

void EscapeMenuScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/menu-buttons.png", "play-button", Engine::Instance()->getRenderer());
    texture_id_list.push_back("play-button");

    Button *start_btn = new Button(
            this,
            Engine::Instance()->WindowSize().w / 2 - 68,
            300,
            136,
            64,
            1,
            2,
            "play-button",
            save,
            "SAVE"
    );

    Button *load_btn = new Button(
            this,
            Engine::Instance()->WindowSize().w / 2 - 68,
            400,
            136,
            64,
            1,
            2,
            "play-button",
            quit,
            "QUIT"
    );

    buttons.push_back(start_btn);
    buttons.push_back(load_btn);

    p_name = this->player_name;
    player_points = this->points;
    player_level = this->level;
    player_lives = this->lives;
}

void EscapeMenuScene::OnExit() {
    for (auto &it: buttons) {
        it->Free();
        delete it;
    }
    buttons.clear();

    for (auto &it: texture_id_list) {
        TextureManager::Instance()->FreeFromTextureMap(it);
    }
}

std::string EscapeMenuScene::GetStateID() { return ID; }