#include "Animal.h"
#include "../../scenes/PlayScene.h"

Animal::Animal(PlayScene *parrent_scene, int x, int y, int width, int height, int animation_speed,
               int num_frames, std::string texture_ID) {
    object_ID = "Animal";

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
}

void Animal::Update() {
    position.setX(position.getX() - parrent_scene->ScenePos());

    collider.x = position.getX();
    collider.y = position.getY();

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

}

void Animal::Draw() {
    EntityObject::Draw();
}

void Animal::Free() {
    EntityObject::Free();
}