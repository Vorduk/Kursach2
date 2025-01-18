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
        renderer->loadTexture("wall1", "image1.png");
        renderer->loadTexture("wall2", "image2.png");
        renderer->loadTexture("wall3", "image3.png");
        renderer->setWallTexture(1, "wall1");
        renderer->setWallTexture(2, "wall2");
        renderer->setWallTexture(3, "wall3");
        renderer->loadTexture("sky", "textures/sky3.jpg");


        while (m_running) {

            cur_scene->getPlayer().setPlayerPrevX();
            cur_scene->getPlayer().setPlayerPrevY();

            handleEvents(cur_scene->getPlayer());

            cur_scene->processPlayerCollision();

            cur_scene->getCamera().synchronizeWithPlayer(cur_scene->getPlayer());

            renderer->clear();
            renderer->renderSceneDDA(*cur_scene);
            renderer->present();

            printf("player: %.2lf\n", cur_scene->getPlayer().getPlayerAngle());
            printf("camera: %.2lf\n", cur_scene->getCamera().getCameraAngle());

            
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
            player.movePlayer(0.07);
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            player.movePlayer(-0.016);
        }

        if (currentKeyStates[SDL_SCANCODE_A]) {
            player.addPlayerAngle(-0.03);
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            player.addPlayerAngle(0.03);
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

