#include <iostream>
#include "src/Engine.h"
#include <vector>
#include <memory>

const float delay_ms = 16.6666666667f; // 60 fps

int main() {
    bool fullscreen = 0;
    std::cout << "Start in fullscreen? [0/1] ";
    std::cin >> fullscreen;

    if (
            !Engine::Instance()->Init
                    (
                            "Hop King",
                            1920,
                            1080,
                            fullscreen
                    )
            )
        return -1;

    Uint64 start, end;

    while (Engine::Instance()->isRunning()) {
        start = SDL_GetPerformanceCounter();

        Engine::Instance()->HandleEvents();
        Engine::Instance()->Update();
        Engine::Instance()->Render();

        end = SDL_GetPerformanceCounter();
        float elapsed_ms = (end - start) / (float) SDL_GetPerformanceFrequency() * 1000.0f;

        SDL_Delay(delay_ms - (elapsed_ms >= delay_ms ? 0 : elapsed_ms)); // in case of no v-sync

//        end = SDL_GetPerformanceCounter();
//        float elapsed = (end - start) / (float) SDL_GetPerformanceFrequency();
//        std::cout << "Current FPS: " << std::to_string(1.0f / elapsed) << std::endl;
    }

    Engine::Instance()->Free();

    return 0;
}
