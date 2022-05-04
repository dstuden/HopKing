#include "Button.h"
#include "../../utils/InputManager.h"
#include "../../utils/TextureManager.h"
#include "../../Engine.h"

Button::Button(GameScene *parrent_scene, int x, int y, int width, int height, int animation_speed, int num_frames,
               std::string texture_ID, void (*function)(), std::string display_text) {

    this->object_ID = "Button";

    callback = function;

    this->parrent_scene = parrent_scene;

    position.setX(x);
    position.setY(y);

    this->width = width;
    this->height = height;

    this->animation_speed = animation_speed;
    this->num_frames = num_frames;

    this->texture_ID = texture_ID;

    font = TTF_OpenFont("../fonts/EquipmentPro.ttf", width / 2);
    text_color = {0, 0, 0};
    surface = TTF_RenderText_Solid(font, display_text.c_str(), text_color);

    texture = SDL_CreateTextureFromSurface(Engine::Instance()->getRenderer(), surface);
    SDL_FreeSurface(surface);

    std::cout << "Created button!\n\n";
}

void Button::Update() {
    if (!InputManager::Instance()->GetKeyState(SDL_SCANCODE_RETURN))
        InputManager::Instance()->SetKey(SDL_SCANCODE_RETURN, false);

    if (selected)
        current_frame = 1;
    else
        current_frame = 0;

    if (selected && InputManager::Instance()->GetKeyState(SDL_SCANCODE_RETURN) &&
        !InputManager::Instance()->KeyPressed(SDL_SCANCODE_RETURN)) {
        InputManager::Instance()->SetKey(SDL_SCANCODE_RETURN, true);
        callback();
    }

}

void Button::Draw() {
    TextureManager::Instance()->Draw(
            this->texture_ID,
            position.getX(),
            position.getY(),
            width,
            height,
            Engine::Instance()->getRenderer(),
            current_frame,
            SDL_FLIP_NONE
    );
    SDL_Rect text_pos = {(int) position.getX() + width / 2 / 2, (int) position.getY() + height / 2 / 2, width / 2,
                         height / 2};
    SDL_RenderCopy(Engine::Instance()->getRenderer(), texture, NULL, &text_pos);

}

void Button::Free() {
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    dead = true;
}
