#include "Player.h"
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

    collider.w = width;
    collider.h = height;

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;

    this->texture_ID = texture_ID;

    this->lives = lives;
}

void Player::Update() {
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_D)) {
        velocity.setX(5);
    }
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_A)) {
        velocity.setX(-5);
    }

    velocity.setY(0);
    position.setX(position.getX() + velocity.getX());
    collider.x = position.getX();
    CheckCollision(); // one of the worst implementations

    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_W)) {
        velocity.setY(-5);
    }
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_S)) {
        velocity.setY(5);
    }

    velocity.setX(0);
    position.setY(position.getY() + velocity.getY());
    collider.y = position.getY();
    CheckCollision();

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

}

void Player::Draw() {
    EntityObject::Draw();
}

void Player::Free() {
    EntityObject::Free();
}

void Player::CheckCollision() {
    for (auto &it: this->parrent_scene->GetGameObjects()) {
        if (this->GetID() == it->GetID()) continue;

        if (SDL_HasIntersection(this->GetRect(), it->GetRect())) {
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

            if (it->GetObjectID() == "LifeUp") {
                EntityObject::AddLife();
            }

            if (it->GetObjectID() == "Platform") {
                position -= velocity;

                collider.x = position.getX();
                collider.y = position.getY();
            }
        }
    }
}

