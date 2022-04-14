#include "Button.h"
#include "../../utils/InputManager.h"
#include "../../utils/TextureManager.h"
#include "../../Engine.h"

Button::Button(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed, int num_frames,
               std::string texture_ID) {

    this->object_ID = "Button";

    this->parrent_scene = parrent_scene;

    position.setX(x);
    position.setY(y);

    this->width = width;
    this->height = height;

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;

    this->texture_ID = texture_ID;

    std::cout << "Created button!\n\n";

}

void Button::Update() {
    if (selected && InputManager::Instance()->GetKeyState(SDL_SCANCODE_RETURN)) {
        selected = false;

        std::cout << "Button pressed!\n";
    }
}

void Button::Draw() {
    EntityObject::Draw();
}

void Button::Free() {
    this->dead = true;
}
