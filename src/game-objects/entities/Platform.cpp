#include "Platform.h"
#include "../../scenes/GameScene.h"
#include "../../utils/TextureManager.h"
#include "../../Engine.h"

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

    if(parrent_scene->Direction() == LEFT)
        velocity.setX(-5);
    else if(parrent_scene->Direction() == RIGHT)
        velocity.setX(5);
    else
        velocity.setX(0);

    position+=velocity;

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

    collider.x = position.getX();
    collider.y = position.getY();

}

void Platform::Draw() {
    TextureManager::Instance()->DrawTile(texture_ID, position.getX(), position.getY(), 64, 64, width, height,
                                           Engine::Instance()->getRenderer(), SDL_FLIP_NONE);
}

void Platform::Free() {

}