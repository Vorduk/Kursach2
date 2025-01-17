#ifndef RENDERER_H
#define RENDERER_H

#include <unordered_map>
#include <SDL.h>
#include "Window.h"
#include "Camera.h"
#include <vector>
#include "TextureManager.h"

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
        TextureManager* m_texture_manager; ///< Texture manager for this renderer
        std::unordered_map<int, std::string> wall_texture_map;

        /**
         * @brief Draws wall textures.
         * @param[in] wall_id -Id of wall on map.
         * @param[in] axis -Axis of wall.
         * @param[in] column -Column on the screen.
         * @param[in] ceiling -Ceiling height.
         * @param[in] height -Height of wall.
         * @param[in] texture_column -Column of pixels on texture to draw
         */
        void drawWallTextures(int wall_id, int axis, int column, int ceiling, int height, int texture_column);

        void drawSkyBox(int ray_angle, int column);

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
        void renderSceneDDA(Camera* camera);

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
         */
        void renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y, bool x_flip, bool y_flip);

        /**
         * @brief Free one texture by id.
         * @param[in] id id of texture.
         */
        void freeTexture(const std::string& id);

        /**
         * @brief Sets the mapping of wall IDs to texture IDs.
         * @param[in] wall_id The numerical ID of the wall.
         * @param[in] texture_id The string ID of the texture.
         */
        void setWallTexture(int wall_id, const std::string& texture_id);
    };

}

#endif // RENDERER_H


