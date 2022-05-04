#include "HealthUp.h"
#include "../../scenes/GameScene.h"
#include "../../utils/TextureManager.h"
#include "../../Engine.h"

HealthUp::HealthUp(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed, int num_frames,
                   std::string texture_ID) {
    object_ID = "HealthUp";

    this->parrent_scene = parrent_scene;

    position.setX(x);
    position.setY(y);

    this->width = width;
    this->height = height;

    collider.w = width;
    collider.h = height;

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;

    this->texture_ID = texture_ID;
}

void HealthUp::Update() {
    position.setX(position.getX() - parrent_scene->ScenePos());

    collider.x = position.getX();
    collider.y = position.getY();

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

}

void HealthUp::Draw() {
    TextureManager::Instance()->Draw(texture_ID, position.getX(), position.getY(),
                                     width, height,
                                     Engine::Instance()->getRenderer(), current_frame, SDL_FLIP_NONE);
}

void HealthUp::Free() {
    EntityObject::Free();
}