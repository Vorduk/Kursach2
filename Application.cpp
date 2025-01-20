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
        renderer->loadTexturesFromScene(*cur_scene);

        //cur_scene->addEnemy(new Zombie(5, 5, 100, 0.05));

        const double enemyUpdateInterval = 1.0 / 20.0;
        double lastEnemyUpdateTime = 0.0;

        auto lastTime = std::chrono::high_resolution_clock::now();

        bool mouseCaptured = true;
        SDL_SetRelativeMouseMode(SDL_TRUE);

        while (m_running) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = currentTime - lastTime;
            lastTime = currentTime;

            cur_scene->getPlayer().setPlayerPrevX();
            cur_scene->getPlayer().setPlayerPrevY();
            handleEvents(cur_scene->getPlayer(), m_windows[0], mouseCaptured);
            cur_scene->processPlayerCollision();

            lastEnemyUpdateTime += elapsed.count();
            if (lastEnemyUpdateTime >= enemyUpdateInterval) {
                cur_scene->updateEnemies();
                lastEnemyUpdateTime = 0.0;
            }

            cur_scene->getCamera().synchronizeWithPlayer(cur_scene->getPlayer());

            renderer->clear();
            renderer->renderSceneDDA(cur_scene);
            renderer->present();

            //printf("player: %.2lf\n", cur_scene->getPlayer().getPlayerAngle());
            //printf("camera: %.2lf\n", cur_scene->getCamera().getCameraAngle());

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

    void Application::handleEvents(Player &player, Window *window, bool& mouseCaptured)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_running = false;
            }

            // Lock cursor
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                mouseCaptured = !mouseCaptured; 
                SDL_SetRelativeMouseMode(mouseCaptured ? SDL_TRUE : SDL_FALSE);
                if (mouseCaptured) {
                    SDL_WarpMouseInWindow(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2);
                }
            }
        }

        // Move player
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            player.movePlayer(0.07);
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            player.movePlayer(-0.016);
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            player.movePlayerSide(0.05);
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            player.movePlayerSide(-0.05);
        }

        int mouse_x, mouse_y;
        SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
        if (mouseCaptured) {
            player.addPlayerAngle(mouse_x * 0.0015);
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

