#pragma once

#include "GameScene.h"
#include "../utils/TextureManager.h"
#include <vector>
#include "GameOverScene.h"
#include "../utils/Vector2D.h"

class PlayScene : public GameScene {
    static std::string ID;

    bool save_loaded;
    std::string player_name;
    int player_points = 0;
    PlayerSave player_save;
    Vector2D player_pos;

    bool completed_current_level = false;
    int num_levels_completed = 0;
    int num_levels = 0;

public:
    PlayScene(bool save_loaded, PlayerSave save) {
        player_save = save;
        this->save_loaded = save_loaded;
    }

    virtual ~PlayScene() override {}

    void CompleteLevel() { completed_current_level = true; }

    void Update() override;

    void Draw() override;

    void OnEnter() override;

    void OnExit() override;

    void SetPlayerPoints(int points) { player_points = points; }

    void SetPlayerPos(Vector2D position) {
        player_pos = position;
    }

    std::string GetStateID() override;
};
