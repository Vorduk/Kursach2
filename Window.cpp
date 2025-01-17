#include "Window.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) //< Macros.

namespace engine
{
    Window::Window(uint width, uint height, std::string caption) : m_width(width), m_height(height), m_caption(caption)
    {
        init(); // SDL initialization.

        // Window creation.
        m_window = SDL_CreateWindow(m_caption.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
        if (!m_window) {
            THROW_ENGINE_EXCEPTION("Failed to create an SDL window.");
            SDL_Quit();
        }
    }

    Window::~Window()
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Window::init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw("Failed to initialize SDL.");
        }
    }

    SDL_Window* Window::getWindow()
    {
        return m_window;
    }

    uint Window::getWidth()
    {
        return m_width;
    }

    uint Window::getHeight()
    {
        return m_height;
    }

} // engine
    
