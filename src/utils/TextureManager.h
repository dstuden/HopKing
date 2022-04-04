#pragma once

#include <map>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager {
    std::map<std::string, SDL_Texture *> texture_map;

    static TextureManager *instance;

    TextureManager() = default;

public:

    ~TextureManager() = default;

    static TextureManager *Instance() {
        if (!instance) {
            instance = new TextureManager;
        }
        return instance;
    }

    bool Load(std::string path, std::string ID, SDL_Renderer *renderer);

    void Draw(std::string ID, int x, int y, int width, int height, SDL_Renderer *renderer,
              int frame,
              SDL_RendererFlip texture_flip);

    void FreeFromTextureMap(std::string ID);

    void Free();
};

