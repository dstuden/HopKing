#include "Player.h"
#include "../Engine.h"
#include "../utils/TextureManager.h"

Player::Player(GameScene *parrent_scene, int x, int y, int texture_width, int texture_height, int animation_speed,
               int num_frames) {
    this->parrent_scene = parrent_scene;

    position.setX(x);
    position.setY(y);

    this->texture_height = texture_height;
    this->texture_width = texture_width;

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;
}

void Player::Update() {
    position += velocity;
}

void Player::Draw() {

    TextureManager::Instance()->Draw("player", position.getX(), position.getY(), texture_width, texture_height,
                                     Engine::Instance()->getRenderer(), )
}