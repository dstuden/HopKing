#include "Player.h"
#include "../../utils/InputManager.h"
#include "../../Engine.h"
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

    collider.x = position.getX();
    collider.y = position.getY();
}

void Player::Update() {
    if (position.getY() > Engine::Instance()->WindowSize().h + 100) { // fell off the map
        lives = 0;
    }

    int x_old = position.getX();

    if (lives <= 0) {
        Free();
        parrent_scene->MoveScene(0); // prevent the camera from moving after death
        return;
    }

    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_D)) {
        velocity.setX(8);
    }
    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_A)) {
        velocity.setX(-8);
    }

    velocity.setY(0);
    position.setX(position.getX() + velocity.getX());
    collider.x = position.getX();
    CheckCollision(); // only for calculating how much the map should move

    parrent_scene->MoveScene(position.getX() - x_old);
    position.setX(x_old);

    if (isFalling()) {
        velocity.setY(15);
    }

    if (isJumping()) {
        if (SDL_GetTicks() - jump_start < 250) {
            velocity.setY(-15);
        } else {
            falling = true;
            jumping = false;
        }
    }

    velocity.setX(0);
    position.setY(position.getY() + velocity.getY());
    collider.y = position.getY();
    CheckCollision();

    if (InputManager::Instance()->GetKeyState(SDL_SCANCODE_SPACE)) {
        if (!isJumping() && !isFalling()) {
            jumping = true;
            jump_start = SDL_GetTicks();
        }
    }

    parrent_scene->SetControllerLives(lives);
    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));
}

void Player::Draw() {
    EntityObject::Draw();
}

void Player::Free() {
    EntityObject::Free();
    parrent_scene->SetControllerLives(0);
}

void Player::CheckCollision() {
    falling = true;

    for (auto &it: this->parrent_scene->GetGameObjects()) {
        if (this->GetID() == it->GetID()) continue;

        if (SDL_HasIntersection(this->GetRect(), it->GetRect())) {
            if (it->GetObjectID() == "Enemy") {
                if (velocity.getY() > 0 &&
                    this->GetRect()->y + this->GetRect()->h <= it->GetRect()->y + 15) // 15 is the jump height
                {
                    it->Hit();
                    invulnerable = true;
                    invulnerability_duration = 1000;
                    invulnerable_start = SDL_GetTicks();
                } else {
                    Hit(1000);
                }

                Uint32 invulnerable_now = SDL_GetTicks() - invulnerable_start;
                if (invulnerable_now > invulnerability_duration)
                    invulnerable = false;
            }

            if (it->GetObjectID() == "LifeUp") {
                EntityObject::AddLife();
            }

            if (it->GetObjectID() == "Platform") {
                if (this->GetRect()->y + this->GetRect()->h <= it->GetRect()->y + 15) // 15 is the jump velocity
                    falling = false;

                if (velocity.getY() != 0 &&
                    this->GetRect()->y + this->GetRect()->h >= it->GetRect()->y + it->GetRect()->h)
                    jumping = false;


                if (velocity.getY() > 0)
                    velocity.setY((position.getY() + height) - it->GetPosition().getY());
                if (velocity.getY() < 0)
                    velocity.setY(position.getY() - (it->GetPosition().getY() + it->GetRect()->h));
                if (velocity.getX() > 0)
                    velocity.setX((position.getX() + width) - it->GetPosition().getX());
                if (velocity.getX() < 0)
                    velocity.setX(position.getX() - (it->GetPosition().getX() + it->GetRect()->w));

                position -= velocity; // only for y

                collider.x = position.getX();
                collider.y = position.getY();
            }
        }
    }
}

