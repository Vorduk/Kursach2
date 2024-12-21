#include "Application.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) // Macros.

namespace engine 
{

    Application::Application() : m_running(true) {}

    Application::~Application()
    {
	    cleanUp();
    }

    void engine::Application::run()
    {
    
        Renderer* renderer = new Renderer(m_windows[0]->getWindow());    

        while (m_running) {
            handleEvents();

            SDL_Color color = { 255, 0, 0, 255 };
            renderer->drawRectangle(100, 100, 200, 150, color);

            renderer->present();

        }

    }

    void Application::createWindow(uint width, uint height, const std::string& caption)
    {
        Window* new_window = new Window(width, height, caption);
        m_windows.push_back(new_window);
    }

    void Application::handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_running = false;
            }
        
            // Key events etc...
        }
    }

    void Application::cleanUp()
    {
        for (Window* window : m_windows) {
            delete window;
            
        }
        m_windows.clear();
    }

} // engine

