#include "Enemy.h"
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
}

void Enemy::Update() {

    if (lives <= 0) {
        Free();
        return;
    }

    if (direction) {
        velocity.setX(-5);
        if(parrent_scene->Direction()==RIGHT)
            velocity.setX(0);
        else if (parrent_scene->Direction()==LEFT)
            velocity.setX(-10);
    }
    else if (!direction) {
        velocity.setX(5);
        if(parrent_scene->Direction()==RIGHT)
            velocity.setX(10);
        else if (parrent_scene->Direction()==LEFT)
            velocity.setX(0);
    }

    velocity.setY(0);
    position.setX(position.getX() + velocity.getX());
    collider.x = position.getX();
    CheckCollision();

    if (isFalling()) {
        velocity.setY(15);
    }

    velocity.setX(0);
    position.setY(position.getY() + velocity.getY());
    collider.y = position.getY();
    CheckCollision();

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

    Uint32 invulnerable_now = SDL_GetTicks() - invulnerable_start;
    if (invulnerable_now > invulnerability_duration)
        invulnerable = false;
}

void Enemy::Draw() {
    EntityObject::Draw();
}

void Enemy::Free() {
    EntityObject::Free();
}

void Enemy::CheckCollision() {
    falling = true;

    for (auto &it: this->parrent_scene->GetGameObjects()) {
        if (this->GetID() == it->GetID()) continue;
        if (it->GetObjectID() != "Platform") continue;

        if (SDL_HasIntersection(this->GetRect(), it->GetRect())) {
            if (it->GetObjectID() == "Platform") {
                if (this->GetRect()->y + this->GetRect()->h <= it->GetRect()->y)
                    falling = false;

                if (this->GetPosition().getX() + this->GetRect()->w >= it->GetRect()->x + it->GetRect()->w)
                    direction = true;
                if (this->GetPosition().getX() <= it->GetRect()->x)
                    direction = false;

                if (velocity.getY() > 0)
                    velocity.setY((position.getY() + height) - it->GetPosition().getY());
                if (velocity.getY() < 0)
                    velocity.setY(position.getY() - (it->GetPosition().getY() + it->GetRect()->h));
                if (velocity.getX() > 0)
                    velocity.setX((position.getX() + width) - it->GetPosition().getX());
                if (velocity.getX() < 0)
                    velocity.setX(position.getX() - (it->GetPosition().getX() + it->GetRect()->w));

                position -= velocity;

                collider.x = position.getX();
                collider.y = position.getY();
            }
        }
    }
}

