#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class InputManager {
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    static InputManager *instance;

    InputManager() = default;

public:

    ~InputManager() = default;

    static InputManager *Instance() {
        if (!instance) {
            instance = new InputManager;
        }
        return instance;
    }

    bool GetKeyState(SDL_Scancode key);

    void Free();
};

