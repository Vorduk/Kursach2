#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <iostream>
#include "EngineException.h"

/**
 * @namespace engine
 * @brief This namespace contains classes for game engine.
 */
namespace engine {

    /**
     * @brief TextureManager class.
     */
    class TextureManager {

    private:
        SDL_Renderer* m_renderer;
        std::map<std::string, SDL_Texture*> m_textures;

    public:
        TextureManager(SDL_Renderer* renderer);
        ~TextureManager();

        /**
         * @brief Loads texture by path and assigns id.
         * @param[in] id id of texture.
         * @param[in] path load path.
         */
        void loadTexture(const std::string& id, const std::string& path);

        /**
         * @brief Draws texture.
         * @param[in] x x cord. of texture (left top angle).
         * @param[in] y y cord. of texture (left top angle).
         * @param[in] render_width width of texture on the screen.
         * @param[in] render_height height of texture on the screen.
         * @param[in] cut_x1 x coordinate of the upper left corner of the clipping area         
         * @param[in] cut_y1 y coordinate of the upper left corner of the clipping area    
         * @param[in] cut_x2 x coordinate of the lower right corner of the clipping area    
         * @param[in] cut_y2 y coordinate of the lower right corner of the clipping area
         * @param x_flip Boolean indicating whether to flip the texture horizontally.
         * @param y_flip Boolean indicating whether to flip the texture vertically.
         *
         * @throws EngineException if the texture with the specified ID is not found.
         */
        void renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2, bool x_flip, bool y_flip);

        /**
         * @brief Free one texture by id.
         * @param[in] id id of texture.
         */
        void freeTexture(const std::string& id);

        /**
         * @brief Clears all textures.
         */
        void clearTextures();
    
    };

}

#endif // !TEXTUREMANAGER_H


