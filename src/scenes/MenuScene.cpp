#include "MenuScene.h"

#include "../Engine.h"

std::string MenuScene::ID = "MENU";

int num_of_buttons = 0;

void MenuScene::Update() {
    static int button = 0;

// need to check for release of a key...
//    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_K) && button < num_of_buttons - 1)
//        button++;
//    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_J) && button > 0)
//        button--;

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

    std::cout << button << std::endl;
}

void MenuScene::Draw() {
    for (auto &it: game_objects) {
        it->Draw();
    }
}

void MenuScene::OnEnter() {
    TextureManager::Instance()->Load("../assets/play-button.png", "play-button", Engine::Instance()->getRenderer());
    texture_id_list.push_back("play-button");

    Button *button1 = new Button(
            this,
            100,
            300,
            128,
            64,
            1,
            1,
            "play-button"
    );

    Button *button2 = new Button(
            this,
            100,
            500,
            128,
            64,
            1,
            1,
            "play-button"
    );

    game_objects.push_back(button1);
    game_objects.push_back(button2);

    for (auto &it: game_objects)
        if (it->GetObjectID() == "Button")
            num_of_buttons++;

    std::cout << "Entered menu!\n\n";
}

void MenuScene::OnExit() {
    for (int i = 0; i <= game_objects.size(); i++) {
        game_objects.back()->Free();
        delete game_objects.back();
        game_objects.pop_back();
    }

    for (auto &it: texture_id_list)
        TextureManager::Instance()->FreeFromTextureMap(it);

}

std::string MenuScene::GetStateID() { return ID; }