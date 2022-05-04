#include "PlayScene.h"
#include "../game-objects/Entities.h"
#include "SceneManager.h"
#include "../utils/LevelLoader.h"
#include "EscapeMenuScene.h"
#include "GameEndScene.h"
#include <fstream>
#include <cstring>

std::string PlayScene::ID = "PLAY";

struct Record {
    char player_name[6] = "";
    int points;
};

void PlayScene::Update() {
    if (controller_lives <= 0) {
        remove("../tmp.txt");
        SceneManager::Instance()->KillBack();
        SceneManager::Instance()->PushScene(new GameOverScene(player_save));
    }

    if (!InputManager::Instance()->GetKeyState(SDL_SCANCODE_ESCAPE))
        InputManager::Instance()->SetKey(SDL_SCANCODE_ESCAPE, false);

    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_ESCAPE) &&
        !InputManager::Instance()->KeyPressed(SDL_SCANCODE_ESCAPE)) {
        InputManager::Instance()->SetKey(SDL_SCANCODE_ESCAPE, true);

        SceneManager::Instance()->KillBack();
        SceneManager::Instance()->PushScene(
                new EscapeMenuScene(player_name, num_levels_completed, player_points, controller_lives));
    }

    if (num_levels_completed == num_levels - 1) {
        std::ofstream player_coords("../tmp.txt", std::ios::app);
        player_coords << scene_controller_pos_diff_x << ' ' << player_pos.getY() << '\n';
        player_coords.close();
    }

    if (completed_current_level) {
        completed_current_level = false;

        for (auto &it: game_objects) {
            it->Free();
            delete it;
        }
        game_objects.clear();

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

        num_levels_completed++;
        if (num_levels_completed >= num_levels) {
            std::cout << player_points << std::endl;
            std::ifstream read_data("../player-saves/records.bin", std::ios::binary);
            std::ofstream write_data("../player-saves/records-tmp.bin", std::ios::app | std::ios::binary);
            if (read_data.is_open() && write_data.is_open()) {
                Record tmp;
                strcpy(tmp.player_name, player_name.c_str());
                tmp.points = player_points;

                bool inserted = false;
                Record a;
                while (read_data.read((char *) &a, sizeof(a))) {
                    if (tmp.points >= a.points && !inserted) {
                        write_data.write((char *) &tmp, sizeof(tmp));
                        inserted = true;
                    }
                    write_data.write((char *) &a, sizeof(a));
                }
            }
            SceneManager::Instance()->KillBack();
            SceneManager::Instance()->PushScene(new GameEndScene);

            write_data.close();
            read_data.close();

            remove("../player-saves/records.bin");
            rename("../player-saves/records-tmp.bin", "../player-saves/records.bin");
        }
        std::ifstream data("../levels/levels.bin", std::ios::binary);
        if (data.is_open()) {
            Level tmp;

            for (int i = 0; i <= num_levels_completed; i++)
                data.read((char *) &tmp, sizeof(tmp));

            data.close();

            LevelLoader::Instance()->LoadLevel(tmp, &game_objects, this);

        } else
            std::cout << "Failed to load level\n";
        data.close();

        Player *player1 = new Player(
                this,
                (Engine::Instance()->WindowSize().w / 2) - 64,
                300,
                42,
                54,
                100,
                11,
                "player",
                this->GetControllerLives()
        );
        player1->SetPoints(player_points);
        game_objects.push_back(player1);

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

void PlayScene::Draw() {
    for (auto &it: game_objects) {
        it->Draw();
    }
    for (int i = 0; i < controller_lives; i++) {
        TextureManager::Instance()->Draw(
                "heart",
                10 + 40 * i,
                10,
                32,
                32,
                Engine::Instance()->getRenderer(),
                0,
                SDL_FLIP_NONE
        );
    }
}

void PlayScene::OnEnter() {
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

    std::ifstream data("../levels/levels.bin", std::ios::binary);

    controller_lives = 5;
    if (save_loaded) {
        controller_lives = player_save.lives;
        player_points = player_save.points;
        num_levels_completed = player_save.level;
    }

    this->player_name = player_save.player_name;

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

    if (data.is_open()) {
        Level tmp;
        while (data.read((char *) &tmp, sizeof(tmp))) {
            num_levels++;
        }
        data.close();

        data.open("../levels/levels.bin", std::ios::binary);
        for (int i = 0; i <= num_levels_completed; i++)
            data.read((char *) &tmp, sizeof(tmp));
        data.close();

        LevelLoader::Instance()->LoadLevel(tmp, &game_objects, this);

    } else
        std::cout << "Failed to load level\n";

    Player *player1 = new Player(
            this,
            (Engine::Instance()->WindowSize().w / 2) - 64,
            300,
            42,
            54,
            100,
            11,
            "player",
            controller_lives
    );

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
}

std::string PlayScene::GetStateID() { return ID; }