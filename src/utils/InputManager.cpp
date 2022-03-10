#include "InputManager.h"

InputManager *InputManager::instance = NULL;

bool InputManager::GetKeyState(SDL_Scancode code) {
    if (key_state[code])
        return true;
    else
        return false;
}

void InputManager::Free() {
    delete this;
}