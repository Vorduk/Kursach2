#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <iostream>

namespace engine {

    class TextureManager {
    public:
        TextureManager(SDL_Renderer* renderer);
        ~TextureManager();

        bool loadTexture(const std::string& id, const std::string& path);
        void renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2);
        void freeTexture(const std::string& id);
        void clearTextures();

    private:
        SDL_Renderer* m_renderer;
        std::map<std::string, SDL_Texture*> m_textures;
    };

}

#endif // TEXTUREMANAGER_H


