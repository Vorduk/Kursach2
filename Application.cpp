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
        Scene* cur_scene = m_scenes[0];

        Renderer* renderer = new Renderer(m_windows[0]);    
        renderer->loadTexture("wall1", "image3.png");
        renderer->loadTexture("wall2", "image.png");
        renderer->setWallTexture(1, "wall1");
        renderer->setWallTexture(2, "wall2");
        renderer->loadTexture("sky1", "sky1.png");
        renderer->loadTexture("sky2", "sky2.png");
        renderer->loadTexture("sky3", "sky3.png");
        renderer->loadTexture("sky4", "sky4.png");

        while (m_running) {
            
            handleEvents(cur_scene->getPlayer());

            renderer->clear();
            renderer->renderSceneDDA(&(cur_scene->getCamera()));
            renderer->present();

            cur_scene->getCamera().synchronizeWithPlayer(cur_scene->getPlayer());
        }

    }

    void Application::addScene(Scene* scene)
    {
        m_scenes.push_back(scene);
    }

    void Application::addWindow(uint width, uint height, const std::string& caption)
    {
        Window* new_window = new Window(width, height, caption);
        m_windows.push_back(new_window);
    }

    void Application::handleEvents(Player &player)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_running = false;
            }
        }

        // Обработка нажатий клавиш
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_W]) {
            player.movePlayer(0.022);
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            player.movePlayer(-0.008);
        }

        if (currentKeyStates[SDL_SCANCODE_A]) {
            player.incrementPlayerAngle(-0.015);
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            player.incrementPlayerAngle(0.015);
        }
    }

    void Application::cleanUp()
    {
        for (Window* window : m_windows) {
            delete window;
            
        }
        m_windows.clear();

        for (Scene* scene : m_scenes) {
            delete scene;

        }
        m_scenes.clear();
    }

} // engine

