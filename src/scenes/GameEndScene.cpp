#include "GameEndScene.h"
#include "../game-objects/entities/Button.h"
#include <SDL2/SDL.h>
#include "../Engine.h"
#include "../utils/InputManager.h"
#include "SceneManager.h"
#include "ReplayScene.h"
#include "PlayScene.h"
#include <fstream>

std::string GameEndScene::ID = "GAMEEND";

struct Record {
    char player_name[6] = "";
    int points;
};

void replay_level() {
    SceneManager::Instance()->PushScene(new ReplayScene);
}

void quitgame() {
    Engine::Instance()->Kill();
}

void GameEndScene::Update() {
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

void GameEndScene::Draw() {
    SDL_RenderCopy(Engine::Instance()->getRenderer(), title_texture, NULL, &title_dest);

    for (auto &it: buttons) {
        it->Draw();
    }

}

void GameEndScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/menu-buttons.png", "play-button", Engine::Instance()->getRenderer());
    texture_id_list.push_back("play-button");

    title_font = TTF_OpenFont("../fonts/FutilePro.ttf", 75);

    title_color = {0, 0, 0};

    Button *replay_btn = new Button(
            this,
            Engine::Instance()->WindowSize().w / 2 - 204,
            550,
            136,
            64,
            1,
            2,
            "play-button",
            replay_level,
            "REPLAY"
    );

    Button *quit_btn = new Button(
            this,
            Engine::Instance()->WindowSize().w / 2 + 68,
            550,
            136,
            64,
            1,
            2,
            "play-button",
            quitgame,
            "QUIT"
    );

    buttons.push_back(replay_btn);
    buttons.push_back(quit_btn);

    std::ifstream data("../player-saves/records.bin", std::ios::binary);
    if (data.is_open()) {
        Record tmp;
        int i = 0;
        while (data.read((char *) &tmp, sizeof(tmp)) && i < 5) {
            scoreboard += tmp.player_name;
            scoreboard += ": ";
            scoreboard += std::to_string(tmp.points);
            scoreboard += "\n";
            i++;
        }
        title_dest = {Engine::Instance()->WindowSize().w / 2 - 250, 0, 500, 75 * (i + 1)};
        title_surface = TTF_RenderText_Blended_Wrapped(title_font, scoreboard.c_str(), title_color, 0);
        title_texture = SDL_CreateTextureFromSurface(Engine::Instance()->getRenderer(), title_surface);
        SDL_FreeSurface(title_surface);
    }
    data.close();
}

void GameEndScene::OnExit() {
    for (auto &it: buttons) {
        it->Free();
        delete it;
    }
    buttons.clear();

    for (auto &it: texture_id_list) {
        TextureManager::Instance()->FreeFromTextureMap(it);
    }

    TTF_CloseFont(title_font);
    SDL_DestroyTexture(title_texture);
}

std::string GameEndScene::GetStateID() { return ID; }