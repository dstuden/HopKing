#pragma once

#include <iostream>
#include <vector>

class EntityObject;
class PlayScene;

/*
 *  For Creating new levels follow this pattern
*/

struct LevelPlatform {
    int x;
    int y;
    int width;
    int height;
    int texture_width;
    int texture_height;
    int animation_speed;
    int num_frames;
    char texture_id[31] = "";
    char type[21] = ""; // to distinguish the type of object when creating it
};

struct LevelEntity {
    int x;
    int y;
    int width;
    int height;
    int animation_speed;
    int num_frames;
    char texture_id[31] = "";
    int lives;
    char type[21] = "";
};

struct Level {
    int num_of_entities;
    int num_of_platforms;
    LevelEntity entities[256]; // 512 max game objects
    LevelPlatform platforms[256];
    bool completed = false;
};

/*
 * Once a level object is created, append it to the level.bin file
*/

class LevelLoader {
    static LevelLoader *instance;

    LevelLoader() = default;

public:

    ~LevelLoader() = default;

    static LevelLoader *Instance() {
        if (!instance) {
            instance = new LevelLoader;
        }
        return instance;
    }

    void LoadLevel(Level level, std::vector<EntityObject *> *game_objects, PlayScene *parrent_scene);

    void Free() {
        delete instance;
    }
};