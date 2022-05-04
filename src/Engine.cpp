#include "Engine.h"
#include "scenes/SceneManager.h"
#include "scenes/MenuScene.h"
#include "scenes/MenuScene.h"

Engine *Engine::instance = NULL;

bool Engine::Init(const char *title, int width, int height, int flags) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    if(TTF_Init() != 0) {
        SDL_Log("Unable to initialize SDL TTF: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
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
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_GetWindowSize(Engine::Instance()->getWindow(), &window_size.w, &window_size.h);

    SceneManager::Instance()->PushScene(new MenuScene);

    running = true;
    return true;
}

void Engine::Update() {
    SceneManager::Instance()->Update();
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

    SceneManager::Instance()->Render();

    SDL_RenderPresent(renderer);
}

void Engine::Free() {
    std::cout << "\nCleaning up...\n\n";

    TextureManager::Instance()->Free();
    std::cout << "Textures destroyed!\n";
    InputManager::Instance()->Free();
    std::cout << "Input modules cleared!\n";
    SceneManager::Instance()->CleanScenes();
    std::cout << "Scenes destroyed!\n";
    SDL_DestroyRenderer(renderer);
    std::cout << "Renderer destroyed!\n";
    SDL_DestroyWindow(window);
    std::cout << "Window destroyed!\n";
    TTF_Quit();
    SDL_Quit();
    std::cout << "\nCleanup successful!\n";
}

SDL_Renderer *Engine::getRenderer() const {
    return renderer;
}

SDL_Window *Engine::getWindow() const {
    return window;
}
