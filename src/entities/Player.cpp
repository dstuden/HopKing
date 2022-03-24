#include "Player.h"
#include "../Engine.h"
#include "../utils/TextureManager.h"
#include "../utils/InputManager.h"
#include "../scenes/Scenes.h"

Player::Player(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
               int num_frames, std::string texture_ID, int lives) {
    this->parrent_scene = parrent_scene;

    position.setX(x);
    position.setY(y);

    this->height = height;
    this->width = width;

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;

    this->texture_ID = texture_ID;

    this->lives = lives;

    std::cout << "Created Player\n\n";
}

void Player::Update() {
    CheckCollision(this->parrent_scene);

    velocity.setX(0);
    velocity.setY(0);

    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_D)) velocity.setX(5);
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_A)) velocity.setX(-5);
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_W)) velocity.setY(-5);
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_S)) velocity.setY(5);

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

    position += velocity;
}

void Player::Draw() {
    TextureManager::Instance()->Draw(texture_ID, position.getX(), position.getY(), width, height, &src_rect, &dest_rect,
                                     Engine::Instance()->getRenderer(), current_frame, SDL_FLIP_NONE);
}

void Player::Free() {
    dead = true;
}

bool Player::CheckCollision(GameScene *parrent) {
    for (auto &it: parrent->GetGameObjects()) {
        if (this->GetID() != it->GetID()) {
            if (SDL_HasIntersection(this->GetRect(), it->GetRect())) {
                position.setX(position.getX() - velocity.getX());
                position.setY(position.getY() - velocity.getY());
            }
        }
    }
}

void Player::AddLife() {
    lives++;
}

