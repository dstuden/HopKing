#include "LevelLoader.h"
#include "../game-objects/Entities.h"
#include "../scenes/PlayScene.h"

LevelLoader *LevelLoader::instance = NULL;

void LevelLoader::LoadLevel(Level tmp, std::vector<EntityObject *> *game_objects, PlayScene *parrent_scene) {
    for (int i = 0; i < tmp.num_of_platforms; i++) {
        if (strcmp(tmp.platforms[i].type, "platform") == 0) {
            game_objects->push_back(
                    new Platform(
                            parrent_scene,
                            tmp.platforms[i].x,
                            tmp.platforms[i].y,
                            tmp.platforms[i].width,
                            tmp.platforms[i].height,
                            tmp.platforms[i].texture_width,
                            tmp.platforms[i].texture_height,
                            tmp.platforms[i].animation_speed,
                            tmp.platforms[i].num_frames,
                            tmp.platforms[i].texture_id
                    )
            );
        } else if (strcmp(tmp.platforms[i].type, "spike") == 0) {
            game_objects->push_back(
                    new Spike(
                            parrent_scene,
                            tmp.platforms[i].x,
                            tmp.platforms[i].y,
                            tmp.platforms[i].width,
                            tmp.platforms[i].height,
                            tmp.platforms[i].texture_width,
                            tmp.platforms[i].texture_height,
                            tmp.platforms[i].animation_speed,
                            tmp.platforms[i].num_frames,
                            tmp.platforms[i].texture_id
                    )
            );
        } else if (strcmp(tmp.platforms[i].type, "endcheckpoint") == 0) {
            game_objects->push_back(
                    new EndCheckpoint(
                            parrent_scene,
                            tmp.platforms[i].x,
                            tmp.platforms[i].y,
                            tmp.platforms[i].width,
                            tmp.platforms[i].height,
                            tmp.platforms[i].texture_width,
                            tmp.platforms[i].texture_height,
                            tmp.platforms[i].animation_speed,
                            tmp.platforms[i].num_frames,
                            tmp.platforms[i].texture_id
                    )
            );
        }
    }

    for (int i = 0; i < tmp.num_of_entities; i++) {
        if (strcmp(tmp.entities[i].type, "enemy") == 0) {
            game_objects->push_back(
                    new Enemy(
                            parrent_scene,
                            tmp.entities[i].x,
                            tmp.entities[i].y,
                            tmp.entities[i].width,
                            tmp.entities[i].height,
                            tmp.entities[i].animation_speed,
                            tmp.entities[i].num_frames,
                            tmp.entities[i].texture_id,
                            tmp.entities[i].lives
                    )
            );
        } else if (strcmp(tmp.entities[i].type, "animal") == 0) {
            game_objects->push_back(
                    new Animal(
                            parrent_scene,
                            tmp.entities[i].x,
                            tmp.entities[i].y,
                            tmp.entities[i].width,
                            tmp.entities[i].height,
                            tmp.entities[i].animation_speed,
                            tmp.entities[i].num_frames,
                            tmp.entities[i].texture_id
                    )
            );

        } else if (strcmp(tmp.entities[i].type, "healthup") == 0) {
            game_objects->push_back(
                    new HealthUp(
                            parrent_scene,
                            tmp.entities[i].x,
                            tmp.entities[i].y,
                            tmp.entities[i].width,
                            tmp.entities[i].height,
                            tmp.entities[i].animation_speed,
                            tmp.entities[i].num_frames,
                            tmp.entities[i].texture_id
                    )
            );

        }
    }
}