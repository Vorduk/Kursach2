#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "Window.h"
#include "Camera.h"
#include <vector>

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

    private:
        SDL_Renderer* m_renderer;
        uint m_width; // Renderer width.
        uint m_height; // Renderer height.
    };

}

#endif // RENDERER_H


