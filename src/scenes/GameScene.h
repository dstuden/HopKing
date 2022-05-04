#pragma once

#include <iostream>
#include <vector>

class EntityObject;

class GameScene {
protected:
    std::vector<std::string> texture_id_list;
    std::vector<EntityObject *> game_objects;
    bool dead = false;
    int scene_controller_pos_diff_x = 0;
    int controller_lives = 0;
    static std::string ID;
public:

    GameScene() = default;

    virtual ~GameScene() { std::cout << "Scene deleted!\n"; }

    virtual void Update() = 0;

    virtual void Draw() = 0;

    virtual void OnExit() = 0;

    virtual void OnEnter() = 0;

    virtual std::string GetStateID() { return ""; }

    std::vector<EntityObject *> GetGameObjects() { return game_objects; }

    int GetControllerLives() {
        return controller_lives;
    }

    void SetControllerLives(int lives) {
        controller_lives = lives;
    }

    bool isDead() { return dead; }

    void Die() { dead = true; }

    void MoveScene(int diff) { scene_controller_pos_diff_x = diff; }

    int ScenePos() { return scene_controller_pos_diff_x; }
};

