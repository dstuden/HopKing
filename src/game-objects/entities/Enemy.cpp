#include "Enemy.h"
#include "../../Engine.h"
#include "../../utils/TextureManager.h"
#include "../../utils/InputManager.h"
#include "../../scenes/Scenes.h"

Enemy::Enemy(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
             int num_frames, std::string texture_ID, int lives) {
    object_ID = "Enemy";

    this->parrent_scene = parrent_scene;

    position.setX(x);
    position.setY(y);

    this->height = height;
    this->width = width;

    collider.w = width;
    collider.h = height;

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;

    this->texture_ID = texture_ID;

    this->lives = lives;

    std::cout << "Created Enemy\n\n";
}

void Enemy::Update() {
    CheckCollision();

    velocity.setX(0);
    velocity.setY(0);

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

    position += velocity;

    collider.x = position.getX();
    collider.y = position.getY();
}

void Enemy::Draw() {
    EntityObject::Draw();
}

void Enemy::Free() {
    EntityObject::Free();
}

void Enemy::CheckCollision() {
    for (auto &it: parrent_scene->GetGameObjects()) {
        if (this->GetID() != it->GetID()) {

        }
    }
}

