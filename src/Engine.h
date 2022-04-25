#pragma once

#include <SDL2/SDL.h>
#include "iostream"

#include "utils/InputManager.h"
#include "utils/TextureManager.h"

class Engine {
    SDL_Renderer *renderer;
public:
    SDL_Renderer *getRenderer() const;

    SDL_Window *getWindow() const;

private:
    SDL_Window *window;

    bool running;

    int width;
    int height;

    static Engine *instance;

    Engine() = default;

    SDL_Rect window_size;

public:
    // Engine class will be a singleton
    static Engine *Instance() {
        if (!instance) {
            instance = new Engine();
        }
        return instance;
    }

    ~Engine() = default;

    bool Init(const char *title, int width, int height, int flags);

    void Update();

    void Render();

    void HandleEvents();

    void Free();

    bool isRunning() { return running; }

    SDL_Rect WindowSize() { return window_size; }
};

