#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class InputManager {
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    bool keys_pressed[512];

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

    bool KeyPressed(int n) { return keys_pressed[n]; }

    void SetKey(int n, bool state) { keys_pressed[n] = state; }

    void Free();
};

