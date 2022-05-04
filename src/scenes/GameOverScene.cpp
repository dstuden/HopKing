#include "GameOverScene.h"
#include "../game-objects/entities/Button.h"
#include "../Engine.h"
#include "SceneManager.h"
#include "PlayScene.h"

std::string GameOverScene::ID = "GAMEOVER";

PlayerSave p;

void quit_game() {
    Engine::Instance()->Kill();
}

void retry() {
    SceneManager::Instance()->KillBack();
    SceneManager::Instance()->PushScene(new PlayScene(false, p));
}

void GameOverScene::Update() {
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


void GameOverScene::Draw() {
    SDL_Rect title_dest = {Engine::Instance()->WindowSize().w / 2 - 200, 0, 400, 200};
    SDL_RenderCopy(Engine::Instance()->getRenderer(), texture, NULL, &title_dest);
    for (auto &it: buttons) {
        it->Draw();
    }
}

void GameOverScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/menu-buttons.png", "play-button", Engine::Instance()->getRenderer());
    texture_id_list.push_back("play-button");

    title_font = TTF_OpenFont("../fonts/FutilePro.ttf", 400);
    title_color = {0, 0, 0};
    surface = TTF_RenderText_Solid(title_font, "GAME OVER", title_color);

    p = this->player;

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
            retry,
            "RETRY"
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
            quit_game,
            "QUIT"
    );

    buttons.push_back(play_btn);
    buttons.push_back(quit_btn);
}

void GameOverScene::OnExit() {
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

std::string GameOverScene::GetStateID() {
    return ID;
}