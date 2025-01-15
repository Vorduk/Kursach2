#ifndef RENDERER_H
#define RENDERER_H

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
        SDL_Renderer* m_renderer;
        uint m_width; // Renderer width.
        uint m_height; // Renderer height.
        TextureManager* m_texture_manager;
    
    public:
        Renderer(Window* window); // Constructor
        ~Renderer(); // Destructor

        void clear(); // Fill black
        void present(); // Show changes

        /**
         * @brief Draws rectangle.
         * @param x x cord.
         * @param y y cord.
         * @param width rectangle width.
         * @param height rectangle height.
         * @param color fill color.
         */
        void drawRectangle(int x, int y, int width, int height, SDL_Color color);

        /**
         * Scene rendering
         * Obstacle rendering with DDA algorithm
         * Enemy and Item rendering
         */
        void renderSceneDDA(Camera* camera);

        bool loadTexture(const std::string& id, const std::string& path);
        void renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2);
        void freeTexture(const std::string& id);
    };

}

#endif // RENDERER_H


