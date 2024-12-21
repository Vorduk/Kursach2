#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <vector>

namespace engine {

    class Renderer {
    public:
        Renderer(SDL_Window* window);
        ~Renderer();

        void clear();
        void present();
        void drawRectangle(int x, int y, int width, int height, SDL_Color color);

    private:
        SDL_Renderer* m_renderer;
    };

}

#endif // RENDERER_H


