#include "Player.h"
#include "../../Engine.h"
#include "../../utils/TextureManager.h"
#include "../../utils/InputManager.h"
#include "../../scenes/Scenes.h"

Player::Player(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
               int num_frames, std::string texture_ID, int lives) {
    object_ID = "Player";

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
    CheckCollision();

    velocity.setX(0);
    velocity.setY(0);

    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_D)) velocity.setX(5);
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_A)) velocity.setX(-5);
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_W)) velocity.setY(-10);
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_S)) velocity.setY(10);

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

    position += velocity;
}

void Player::Draw() {
    TextureManager::Instance()->Draw(texture_ID, position.getX(), position.getY(), width, height, &dest_rect,
                                     Engine::Instance()->getRenderer(), current_frame, SDL_FLIP_NONE);
}

void Player::Free() {
    dead = true;
}

bool Player::CheckCollision() {
    for (auto &it: this->parrent_scene->GetGameObjects()) {
        if (this->GetID() == it->GetID()) continue;

        SDL_Rect result;
        if (SDL_IntersectRect(this->GetRect(), it->GetRect(), &result)) {
            if (it->GetObjectID() == "Enemy") {
                if (!isInvoulnerable()) {
                    if (--lives < 0)
                        Free();
                    invulnerable = true;
                    invulnerable_start = SDL_GetTicks();
                } else {
                    Uint32 invulnerable_now = SDL_GetTicks() - invulnerable_start;
                    if (invulnerable_now > 1000)
                        invulnerable = false;
                }
            }

            if (it->GetObjectID() == "HealthUp") {
                this->AddLife();
            }

            if (it->GetObjectID() == "Enemy") {
                std::cout << result.x << std::endl;
            }
        }

    }
}

void Player::AddLife() {
    lives++;
}

