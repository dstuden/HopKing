#include "TextureManager.h"

TextureManager *TextureManager::instance = NULL;

bool TextureManager::Load(std::string path, std::string ID, SDL_Renderer *renderer) {
    SDL_Surface *surface = IMG_Load(path.c_str());

    if (!surface) {
        std::cout << "Failed to load image!\n";
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture) {
        texture_map[ID] = texture;
        return true;
    }

    std::cout << "Failed to create texture!\n";
    return false;
}

void TextureManager::Draw(std::string ID, int x, int y, int width, int height, SDL_Renderer *renderer,
                          int frame,
                          SDL_RendererFlip texture_flip = SDL_FLIP_NONE) {
    SDL_Rect src_rect;
    SDL_Rect dest_rect;
    src_rect.w = dest_rect.w = width;
    src_rect.h = dest_rect.h = height;

    src_rect.x = width * frame;
    src_rect.y = 0;

    dest_rect.x = x;
    dest_rect.y = y;

    SDL_RenderCopyEx(
            renderer,
            texture_map[ID],
            &src_rect,
            &dest_rect,
            0,
            0,
            texture_flip
    );
}

void TextureManager::FreeFromTextureMap(std::string ID) {
    SDL_DestroyTexture(texture_map[ID]);
    texture_map.erase(ID);
}

void TextureManager::Free() {
    for (auto &it: texture_map) {
        SDL_DestroyTexture(it.second);
    }
    texture_map.clear();
    delete instance;
}