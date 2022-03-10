#include "Engine.h"

Engine *Engine::instance = NULL;

bool Engine::Init(const char *title, int width, int height, int flags) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            flags
    );

    if (!window) {
        printf("Could not create window: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    TextureManager::Instance()->Load("../assets/player.png", "player", renderer);

    running = true;
    return true;
}

void Engine::Update() {
    if(InputManager::Instance()->GetKeyState(SDL_SCANCODE_RETURN))
        std::cout<<"Return Pressed!\n";
}

void Engine::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;

            default:
                break;
        }
    }
}

void Engine::Render() {
    SDL_RenderClear(renderer);

    TextureManager::Instance()->Draw("player", 200, 200, 64, 64, renderer, 0, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);
}

void Engine::Free() {
    TextureManager::Instance()->Free();
    InputManager::Instance()->Free();

    std::cout << "\nCleaning up...\n";
    SDL_DestroyRenderer(renderer);
    std::cout << "Renderer destroyed!\n";
    SDL_DestroyWindow(window);
    std::cout << "Window destroyed!\n";
    SDL_Quit();
    std::cout << "Cleanup successful!\n";
}

SDL_Renderer *Engine::getRenderer() const {
    return renderer;
}

SDL_Window *Engine::getWindow() const {
    return window;
}
