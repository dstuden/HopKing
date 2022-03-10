#include <iostream>
#include "src/Engine.h"

const float delay_ms = 16.6666666667f; // 60 fps

int main() {

    if (
            !Engine::Instance()->Init
                    (
                            "Hop King",
                            800,
                            640,
                            0
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

        SDL_Delay(delay_ms - (elapsed_ms >= delay_ms ? 0 : elapsed_ms));

//        end = SDL_GetPerformanceCounter();
//        float elapsed = (end - start) / (float) SDL_GetPerformanceFrequency();
//        std::cout << "Current FPS: " << std::to_string(1.0f / elapsed) << std::endl;
    }

    Engine::Instance()->Free();

    return 0;
}
