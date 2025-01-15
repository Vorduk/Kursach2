#include "TextureManager.h"

namespace engine {

    TextureManager::TextureManager(SDL_Renderer* renderer) : m_renderer(renderer) {}

    TextureManager::~TextureManager() {
        clearTextures();
    }

    bool TextureManager::loadTexture(const std::string& id, const std::string& path) {
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (!loadedSurface) {
            std::cerr << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
            return false;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);

        if (!texture) {
            std::cerr << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_textures[id] = texture;
        return true;
    }

    void TextureManager::renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2)
    {
        SDL_Texture* texture = m_textures[texture_id];
        if (texture) {
            SDL_Rect renderQuad = { x, y, render_width, render_height };

            SDL_Rect clip;
            clip.x = cut_x1;
            clip.y = cut_y1;
            clip.w = cut_x2;
            clip.h = cut_y2;

            SDL_RenderCopy(m_renderer, texture, &clip, &renderQuad);
        }
        else {
            std::cerr << "Texture with ID " << texture_id << " not found!" << std::endl;
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
