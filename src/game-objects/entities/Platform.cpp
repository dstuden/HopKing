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

    position.setX(position.getX() - parrent_scene->ScenePos());

    collider.x = position.getX();
    collider.y = position.getY();

    current_frame = int(((SDL_GetTicks() / animation_speed) % num_frames));

}

void Platform::CheckCollision() {
    for (auto &it: this->parrent_scene->GetGameObjects()) {
        if (this->GetObjectID() == it->GetObjectID()) continue;

        if (SDL_HasIntersection(this->GetRect(), it->GetRect())) {

        }
    }
}

void Platform::Draw() {
    TextureManager::Instance()->DrawTile(texture_ID, position.getX(), position.getY(), 64, 64, width, height,
                                         Engine::Instance()->getRenderer(), SDL_FLIP_NONE);
}

void Platform::Free() {

}