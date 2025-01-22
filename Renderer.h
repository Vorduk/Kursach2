#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "Camera.h"
#include "Scene.h"
#include <array>
#include <vector>
#include "EngineException.h"
#include <unordered_map>
#include <iostream>
#include <map>
#include <SDL_image.h>
#include <algorithm>

typedef unsigned int uint;

/**
 * @namespace engine
 * @brief This namespace contains classes for game engine.
 */
namespace engine {

    /**
     * @brief Renderer class.
     */
    class Renderer {

    private:
        SDL_Renderer* m_renderer; ///< SDL renderer.
        uint m_width; ///< Renderer width.
        uint m_height; ///< Renderer height.
        std::unordered_map<int, std::string> m_column_texture_map;
        std::map<std::string, SDL_Texture*> m_textures;
        std::unordered_map<std::string, std::pair<int, int>> m_texture_sizes;
        std::unordered_map<std::string, TTF_Font*> m_fonts; ///< Map to store loaded fonts.

        /**
         * @brief Draws wall textures.
         * @param[in] wall_id -Id of wall on map.
         * @param[in] axis -Axis of wall.
         * @param[in] column -Column on the screen.
         * @param[in] ceiling -Ceiling height.
         * @param[in] height -Height of wall.
         * @param[in] texture_column -Column of pixels on texture to draw
         */
        void drawWallTextures(int wall_id, int axis, int column, int ceiling, int height, int texture_column, std::array<float, 3>& fog_factors);

        void drawSkyBox(double ray_angle, int column);

    public:
        Renderer(Window* window); ///< Constructor
        ~Renderer(); ///< Destructor

        void clear(); ///< Fill black
        void present(); ///< Show changes

        /**
         * @brief Draws rectangle.
         * @param[in] x x cord.
         * @param[in] y y cord.
         * @param[in] width rectangle width.
         * @param[in] height rectangle height.
         * @param[in] color fill color.
         */
        void drawRectangle(int x, int y, int width, int height, SDL_Color color);

        /**
         * Scene rendering
         * Obstacle rendering with DDA algorithm
         * Enemy and Item rendering
         */
        void renderSceneDDA(Scene* scene);

        /**
         * @brief Sets the mapping of wall IDs to texture IDs.
         * @param[in] wall_id The numerical ID of the wall.
         * @param[in] texture_id The string ID of the texture.
         */
        void setWallTexture(int wall_id, const std::string& texture_id);

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
        void renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2, bool x_flip, bool y_flip, std::array<float, 3>& fog_factors);

        /**
         * @brief Free one texture by id.
         * @param[in] id id of texture.
         */
        void freeTexture(const std::string& id);

        /**
         * @brief Clears all textures.
         */
        void clearTextures();

        /**
         * @brief Loads a font from a file and associates it with a given ID.
         * @param[in] id The ID to associate with the font.
         * @param[in] path The file path of the font.
         * @param[in] font_size The size of the font.
         * @throws EngineException if the font cannot be loaded.
         */
        void loadFont(const std::string& id, const std::string& path, int font_size);

        /**
         * @brief Renders a text string at the specified coordinates using the specified font ID.
         * @param[in] font_id The ID of the font to use.
         * @param[in] text The text string to render.
         * @param[in] x The x coordinate to render the text.
         * @param[in] y The y coordinate to render the text.
         * @param[in] color The color of the text.
         * @throws EngineException if the font ID is not found or rendering fails.
         */
        void renderText(const std::string& font_id, const std::string& text, int x, int y, SDL_Color color);

        /**
         * @brief Frees all loaded fonts.
         */
        void clearFonts();

        void loadTexturesFromScene(const Scene& scene);

        void drawFloor();

        void renderSprite(Scene* scene, Sprite sprite, std::string stick, std::vector<double> distances_mask);
    };

} // engine

#endif // RENDERER_H


