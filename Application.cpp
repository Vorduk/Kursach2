#include "Application.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) // Macros.

void button1Action() {
    std::cout << "Button 1 clicked!" << std::endl;
}

namespace engine 
{

    Application::Application() : m_running(true) {}

    Application::~Application()
    {
	    cleanUp();
    }

    void engine::Application::run()
    {
        addUI();

        Scene* cur_scene = m_scenes[0];

        Renderer* renderer = new Renderer(m_windows[0]);   
        renderer->loadTexturesFromScene(*cur_scene);

        renderer->loadFont("arial", "fonts/ofont.ru_Arial.ttf", 25);
        SDL_Color font_color = { 255, 255, 255, 255 };

        const double enemyUpdateInterval = 1.0 / 20.0;
        const double animationUpdateInterval = 1.0 / 4.0;
        double lastEnemyUpdateTime = 0.0;
        double lastAnimationUpdateTime = 0.0;

        auto lastTime = std::chrono::high_resolution_clock::now();

        bool mouseCaptured = true;
        SDL_SetRelativeMouseMode(SDL_TRUE);

        m_ui.m_buttons.emplace_back(100, 100, 200, 50, "Button 1", button1Action);

        int fps = 0;

        while (m_running) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = currentTime - lastTime;
            lastTime = currentTime;

            cur_scene->getPlayer().setPlayerPrevX();
            cur_scene->getPlayer().setPlayerPrevY();
            handleEvents(*cur_scene, m_windows[0], mouseCaptured);
            cur_scene->processPlayerCollision();

            lastEnemyUpdateTime += elapsed.count();
            lastAnimationUpdateTime += elapsed.count();
            if (lastEnemyUpdateTime >= enemyUpdateInterval) {
                cur_scene->updateEnemies();
                lastEnemyUpdateTime = 0.0;
                fps = static_cast<int>(1.0 / elapsed.count());
            }
            if (lastAnimationUpdateTime >= animationUpdateInterval) {
                cur_scene->updateAnimations();
                lastAnimationUpdateTime = 0.0;
            }

            cur_scene->getCamera().synchronizeWithPlayer(cur_scene->getPlayer());

            renderer->clear();
            renderer->renderSceneDDA(cur_scene);
            renderer->drawText("arial", std::to_string(fps), 5, 5, font_color);
            renderer->drawText("arial", std::to_string(cur_scene->getPlayer().getPlayerHealth()), 5, 30, font_color);
            renderer->drawText("arial", std::to_string(cur_scene->getEnemyCount()), 5, 55, font_color);
            renderer->drawUI(m_ui);
            renderer->present(); 

            if (cur_scene->getPlayer().getPlayerHealth() <= 0) {
                m_running = false;
            }
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

    void Application::addUI()
    {
        m_ui = UI();
    }

    void Application::handleEvents(Scene &scene, Window *window, bool& mouseCaptured)
    {
        SDL_Event event;
        int mouse_x, mouse_y;
        int abs_mouse_x, abs_mouse_y;
        SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
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

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT && mouseCaptured == false) {
                    SDL_GetMouseState(&abs_mouse_x, &abs_mouse_y);;
                    for (auto& button : m_ui.m_buttons) {
                        button.handleClick(abs_mouse_x, abs_mouse_y);
                    }

                    mouseCaptured = true;
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                }

                if (event.button.button == SDL_BUTTON_LEFT && mouseCaptured == true) {
                    scene.fire();
                }
            }
        }

        // Move player
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            scene.getPlayer().movePlayer(0.07);
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            scene.getPlayer().movePlayer(-0.016);
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            scene.getPlayer().movePlayerSide(0.04);
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            scene.getPlayer().movePlayerSide(-0.04);
        }
        

        if (mouseCaptured) {
            scene.getPlayer().addPlayerAngle(mouse_x * 0.0015);
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

