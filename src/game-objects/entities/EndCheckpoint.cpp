#include "EndCheckpoint.h"
#include "../../scenes/GameScene.h"
#include "../../utils/TextureManager.h"
#include "../../Engine.h"

EndCheckpoint::EndCheckpoint(GameScene *parrent_scene, int x, int y, int width, int height, int texture_width, int texture_height,
             int animation_speed, int num_frames,
             std::string texture_ID) {
    object_ID = "EndCheckpoint";

    this->parrent_scene = parrent_scene;

    position.setX(x);
    position.setY(y);

    this->width = width;
    this->height = height;

    this->texture_width = texture_width;
    this->texture_height = texture_height;

    collider.w = width;
    collider.h = height;

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;

    this->texture_ID = texture_ID;
}

void EndCheckpoint::Update() {

    position.setX(position.getX() - parrent_scene->ScenePos());

    collider.x = position.getX();
    collider.y = position.getY();

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

}

void EndCheckpoint::Draw() {
    TextureManager::Instance()->DrawTile(texture_ID, position.getX(), position.getY(), texture_width, texture_height,
                                         width, height,
                                         Engine::Instance()->getRenderer(), SDL_FLIP_NONE);
}

void EndCheckpoint::Free() {
    EntityObject::Free();
}