#include "MenuScene.h"
#include "../game-objects/entities/Button.h"
#include "../Engine.h"
#include "SceneManager.h"
#include "PlaySelectScene.h"

std::string MenuScene::ID = "PLAY";

void start_function() {
    SceneManager::Instance()->KillBack();
    SceneManager::Instance()->PushScene(new PlaySelectScene);
}

void quit_function() {
    Engine::Instance()->Kill();
}

void MenuScene::Update() {
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


void MenuScene::Draw() {
    SDL_Rect title_dest = {Engine::Instance()->WindowSize().w / 2 - 200, 0, 400, 200};
    SDL_RenderCopy(Engine::Instance()->getRenderer(), texture, NULL, &title_dest);
    for (auto &it: buttons) {
        it->Draw();
    }
}

void MenuScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/menu-buttons.png", "play-button", Engine::Instance()->getRenderer());
    texture_id_list.push_back("play-button");

    title_font = TTF_OpenFont("../fonts/FutilePro.ttf", 400);
    title_color = {0, 0, 0};
    surface = TTF_RenderText_Solid(title_font, "Hop King", title_color);

    texture = SDL_CreateTextureFromSurface(Engine::Instance()->getRenderer(), surface);
    SDL_FreeSurface(surface);

    Button *play_btn = new Button(
            this,
            Engine::Instance()->WindowSize().w / 2 - 68,
            300,
            136,
            64,
            1,
            2,
            "play-button",
            &start_function,
            "START"
    );

    Button *quit_btn = new Button(
            this,
            Engine::Instance()->WindowSize().w / 2 - 68,
            400,
            136,
            64,
            1,
            2,
            "play-button",
            &quit_function,
            "QUIT"
    );

    buttons.push_back(play_btn);
    buttons.push_back(quit_btn);
}

void MenuScene::OnExit() {
    for (auto &it: buttons) {
        it->Free();
        delete it;
    }
    buttons.clear();

    for (auto &it: texture_id_list) {
        TextureManager::Instance()->FreeFromTextureMap(it);
    }

    SDL_DestroyTexture(texture);
    TTF_CloseFont(title_font);
}

std::string MenuScene::GetStateID() {
    return ID;
}