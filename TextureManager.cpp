#include "TextureManager.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) //< Macros.

namespace engine {

    TextureManager::TextureManager(SDL_Renderer* renderer) : m_renderer(renderer) {}

    TextureManager::~TextureManager() {
        clearTextures();
    }

    void TextureManager::loadTexture(const std::string& id, const std::string& path) {
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (!loadedSurface) {
            std::string sdl_image_error = IMG_GetError();
            THROW_ENGINE_EXCEPTION("SDL_image failed: " + sdl_image_error + ".");
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);

        if (!texture) {
            std::string sdl_texture_error = SDL_GetError();
            THROW_ENGINE_EXCEPTION("Failed to create texture: " + sdl_texture_error + ".");
        }

        m_textures[id] = texture;
    }

    void TextureManager::renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2, bool x_flip, bool y_flip)
    {
        SDL_Texture* texture = m_textures[texture_id];
        if (texture) {
            // Define the area to render the texture
            SDL_Rect renderQuad = { x, y, render_width, render_height };

            // Define the clipping area
            SDL_Rect clip;
            clip.x = cut_x1;
            clip.y = cut_y1;
            clip.w = cut_x2 - cut_x1; // Ensure the width is correct
            clip.h = cut_y2 - cut_y1; // Ensure the height is correct

            // Determine flip flags
            SDL_RendererFlip flip = SDL_FLIP_NONE; // Initial value - no flip
            if (x_flip) {
                flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
            }
            if (y_flip) {
                flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
            }

            // Render the texture with the specified clipping and flipping
            SDL_RenderCopyEx(m_renderer, texture, &clip, &renderQuad, 0.0, nullptr, flip);
        }
        else {
            THROW_ENGINE_EXCEPTION("Texture with id " + texture_id + " not found.");
        }
    }

    void TextureManager::freeTexture(const std::string& id) {
        if (m_textures.count(id)) {
            SDL_DestroyTexture(m_textures[id]);
            m_textures.erase(id);
        }
    }

    void TextureManager::clearTextures() {
        for (auto& pair : m_textures) {
            SDL_DestroyTexture(pair.second);
        }
        m_textures.clear();
    }

}
