#include "Platform.h"

Platform::Platform(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed, int num_frames,
                   std::string texture_ID) {
    object_ID = "Platform";

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

void Platform::Update() {

}

void Platform::Draw() {

}

void Platform::Free() {

}