#include "Window.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) // Macros.

engine::Window::Window(uint width, uint height, std::string name) : m_width(width), m_height(height), m_name(name)
{
    init(); // SDL initialization.

    /**
     * @brief Window creation.
     */
    SDL_Window* window = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
    if (!window) {
        THROW_ENGINE_EXCEPTION("Failed to create an SDL window.");
        SDL_Quit();
    }
}

engine::Window::~Window()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

/**
 * @brief SDL initialization (SDL_INIT_VIDEO).
 */
void engine::Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw("Failed to initialize SDL.");
    }
}
