#include "PlaySelectScene.h"
#include "../game-objects/entities/Button.h"
#include <SDL2/SDL.h>
#include "../Engine.h"
#include "../utils/InputManager.h"
#include "SceneManager.h"
#include "PlaySelectScene.h"
#include "PlayScene.h"
#include <fstream>

std::string PlaySelectScene::ID = "PLAYSELECT";

struct PlayerSave tmp;

void play_new() {
    SceneManager::Instance()->KillBack();
    SceneManager::Instance()->PushScene(new PlayScene(false, tmp));
}

void load_save() {
    SceneManager::Instance()->KillBack();
    SceneManager::Instance()->PushScene(new PlayScene(true, tmp));
}

void PlaySelectScene::Update() {
    PlayerSave a;

    if (!player_selected) {
        for (auto a = 4; a <= 29; a++) { // SDL_SCANCODE_A to SDL_SCANCODE_Z
            if (!InputManager::Instance()->GetKeyState(static_cast<SDL_Scancode>(a)))
                InputManager::Instance()->SetKey(a, false);

            if (InputManager::Instance()->GetKeyState(static_cast<SDL_Scancode>(a)) &&
                !InputManager::Instance()->KeyPressed(a)) {
                InputManager::Instance()->SetKey(a, true);

                if (player_name.size() < 5)
                    player_name += (char) (a + 61);
            }
        }

        if (!InputManager::Instance()->GetKeyState(SDL_SCANCODE_BACKSPACE)) {
            InputManager::Instance()->SetKey(SDL_SCANCODE_BACKSPACE, false);
        }

        if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_BACKSPACE) &&
            !InputManager::Instance()->KeyPressed(SDL_SCANCODE_BACKSPACE)) {
            InputManager::Instance()->SetKey(SDL_SCANCODE_BACKSPACE, true);
            if (!player_name.empty())
                player_name.pop_back();
        }

        if (!InputManager::Instance()->GetKeyState(SDL_SCANCODE_RETURN)) {
            InputManager::Instance()->SetKey(SDL_SCANCODE_RETURN, false);
        }

        if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_RETURN) &&
            !InputManager::Instance()->KeyPressed(SDL_SCANCODE_RETURN) && !player_name.empty()) {
            InputManager::Instance()->SetKey(SDL_SCANCODE_RETURN, true);
            player_selected = true;

            strcpy(tmp.player_name, player_name.c_str());

            std::ifstream data("../player-saves/saves.bin", std::ios::binary);
            if (data.is_open()) {
                while (data.read((char *) &a, sizeof(a))) {
                    if (strcmp(a.player_name, player_name.c_str()) == 0) {
                        save_found = true;
                        tmp = a;
                        break;
                    }
                }
            }
            if (!save_found) {
                buttons.back()->Free();
                delete buttons.back();
                buttons.pop_back();
            }
            data.close();
        }
    } else {
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
}

void PlaySelectScene::Draw() {
    if (!player_selected) {
        SDL_Surface *title_surface;
        SDL_Texture *title_texture;

        title_surface = TTF_RenderText_Solid(title_font, "Enter Username", title_color);
        title_texture = SDL_CreateTextureFromSurface(Engine::Instance()->getRenderer(), title_surface);
        SDL_FreeSurface(title_surface);
        SDL_Rect title_dest = {Engine::Instance()->WindowSize().w / 2 - 250, 0, 500, 100};
        SDL_RenderCopy(Engine::Instance()->getRenderer(), title_texture, NULL, &title_dest);
        SDL_DestroyTexture(title_texture);


        SDL_Surface *player_name_surface;
        SDL_Texture *player_name_texture;

        player_name_surface = TTF_RenderText_Solid(player_name_render, player_name.c_str(), title_color);
        player_name_texture = SDL_CreateTextureFromSurface(Engine::Instance()->getRenderer(), player_name_surface);
        SDL_FreeSurface(player_name_surface);
        SDL_Rect player_name_dest = {
                static_cast<int>(Engine::Instance()->WindowSize().w / 2 - (48 * player_name.size()) / 2), 300,
                static_cast<int>(48 * player_name.size()), 100};
        SDL_RenderCopy(Engine::Instance()->getRenderer(), player_name_texture, NULL, &player_name_dest);
        SDL_DestroyTexture(player_name_texture);
    } else {
        for (auto &it: buttons) {
            it->Draw();
        }
    }
}

void PlaySelectScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/menu-buttons.png", "play-button", Engine::Instance()->getRenderer());
    texture_id_list.push_back("play-button");

    title_font = TTF_OpenFont("../fonts/FutilePro.ttf", 500);
    player_name_render = TTF_OpenFont("../fonts/FutilePro.ttf", 500);

    title_color = {0, 0, 0};

    Button *start_btn = new Button(
            this,
            Engine::Instance()->WindowSize().w / 2 - 68,
            300,
            136,
            64,
            1,
            2,
            "play-button",
            play_new,
            "PLAY"
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
            load_save,
            "LOAD"
    );

    buttons.push_back(start_btn);
    buttons.push_back(load_btn);
}

void PlaySelectScene::OnExit() {
    for (auto &it: buttons) {
        it->Free();
        delete it;
    }
    buttons.clear();

    for (auto &it: texture_id_list) {
        TextureManager::Instance()->FreeFromTextureMap(it);
    }

    TTF_CloseFont(title_font);
    TTF_CloseFont(player_name_render);
}

std::string PlaySelectScene::GetStateID() { return ID; }