#include "Window.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) //< Macros.

namespace engine
{
    /**
     * @brief Constructor.
     * @param[in] width -Window width (pixels).
     * @param[in] height -Window height (pixels).
     * @param[in] caption -Window caption.
     */
    Window::Window(uint width, uint height, std::string caption) : m_width(width), m_height(height), m_caption(caption)
    {
        init(); // SDL initialization.

        /**
         * @brief Window creation.
         */
        m_window = SDL_CreateWindow(m_caption.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
        if (!m_window) {
            THROW_ENGINE_EXCEPTION("Failed to create an SDL window.");
            SDL_Quit();
        }
    }

    /**
     * @brief Window destructor.
     */
    Window::~Window()
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    /**
     * @brief SDL initialization (SDL_INIT_VIDEO).
     */
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
}
    
