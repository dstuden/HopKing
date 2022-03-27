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

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;

    this->texture_ID = texture_ID;

    this->lives = lives;

    std::cout << "Created Enemy\n\n";
}

void Enemy::Update() {
    CheckCollision(parrent_scene);

    velocity.setX(0);
    velocity.setY(0);

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

    position += velocity;
}

void Enemy::Draw() {
    TextureManager::Instance()->Draw(texture_ID, position.getX(), position.getY(), width, height, &dest_rect,
                                     Engine::Instance()->getRenderer(), current_frame, SDL_FLIP_NONE);
}

void Enemy::Free() {
    dead = true;
}

bool Enemy::CheckCollision(GameScene *parrent) {
    for (auto &it: parrent->GetGameObjects()) {
        if (this->GetID() != it->GetID()) {

        }
    }
}

void Enemy::AddLife() {
    lives++;
}

