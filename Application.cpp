#include "Application.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) // Macros.

namespace engine 
{
    void buttonPlayAction(WindowState& m_current_window_state)
    {
        std::cout << "Button 1 clicked!" << std::endl;
    }

    Application::Application() : m_running(true), m_current_window_state(MENU) {}

    Application::~Application()
    {
	    cleanUp();
    }

    void engine::Application::run()
    {
        addUI();

        Renderer* renderer = new Renderer(m_window);
        renderer->loadFont("arial", "fonts/ofont.ru_Arial.ttf", 25);
        renderer->loadTexture("menu_bg", "textures/menu_bg.jpg");

        while (m_running) {
            handleUIEvents();

            renderer->clear();

            if (m_current_window_state == MENU) {
                std::array<float, 3> fog_factors = { 1.0, 1.0, 1.0 };
                renderer->drawTexture("menu_bg", 0, 0, m_window->getWidth(), m_window->getHeight(), 0, 0, 800, 600, false, false, fog_factors);
                renderer->drawUI(m_ui);
            }
            
            renderer->present();
        }







        //Scene* cur_scene = m_scenes[0];

        //Renderer* renderer = new Renderer(m_window);   
        //renderer->loadTexturesFromScene(*cur_scene);

        //renderer->loadFont("arial", "fonts/ofont.ru_Arial.ttf", 25);
        //SDL_Color font_color = { 255, 255, 255, 255 };

        //const double enemyUpdateInterval = 1.0 / 20.0;
        //const double animationUpdateInterval = 1.0 / 4.0;
        //double lastEnemyUpdateTime = 0.0;
        //double lastAnimationUpdateTime = 0.0;

        //auto lastTime = std::chrono::high_resolution_clock::now();

        //bool mouseCaptured = true;
        //SDL_SetRelativeMouseMode(SDL_TRUE);

        //int fps = 0;

        //while (m_running) {
        //    auto currentTime = std::chrono::high_resolution_clock::now();
        //    std::chrono::duration<double> elapsed = currentTime - lastTime;
        //    lastTime = currentTime;

        //    cur_scene->getPlayer().setPlayerPrevX();
        //    cur_scene->getPlayer().setPlayerPrevY();  
        //    cur_scene->processPlayerCollision();

        //    lastEnemyUpdateTime += elapsed.count();
        //    lastAnimationUpdateTime += elapsed.count();
        //    if (lastEnemyUpdateTime >= enemyUpdateInterval) {
        //        cur_scene->updateEnemies();
        //        lastEnemyUpdateTime = 0.0;
        //        fps = static_cast<int>(1.0 / elapsed.count());
        //    }
        //    if (lastAnimationUpdateTime >= animationUpdateInterval) {
        //        cur_scene->updateAnimations();
        //        lastAnimationUpdateTime = 0.0;
        //    }

        //    cur_scene->getCamera().synchronizeWithPlayer(cur_scene->getPlayer());

        //    renderer->clear();
        //    renderer->renderSceneDDA(cur_scene);
        //    renderer->drawGun(false);
        //    handleEvents(*cur_scene, renderer, m_window, mouseCaptured);
        //    //renderer->drawText("arial", std::to_string(fps), 5, 5, font_color);
        //    //renderer->drawText("arial", std::to_string(cur_scene->getPlayer().getPlayerHealth()), 5, 30, font_color);
        //    //renderer->drawText("arial", std::to_string(cur_scene->getEnemyCount()), 5, 55, font_color);
        //    //renderer->drawUI(m_ui);
        //    renderer->present(); 

        //    if (cur_scene->getPlayer().getPlayerHealth() <= 0) {
        //        m_running = false;
        //    }
        //}

    }

    void Application::addScene(Scene* scene)
    {
        m_scenes.push_back(scene);
    }

    void Application::setWindow(uint width, uint height, const std::string& caption)
    {
        m_window = new Window(width, height, caption);
    }

    void Application::addUI()
    {
        m_ui = UI();
        int win_w = m_window->getWidth() / 2;
        int win_h = m_window->getHeight() / 2;
        int main_menu_buttons_width = 400;
        int main_menu_buttons_height = 50;
        m_ui.m_buttons.emplace_back(win_w - main_menu_buttons_width/2, 220, main_menu_buttons_width, main_menu_buttons_height, "Continue from last save", buttonPlayAction);
        m_ui.m_buttons.emplace_back(win_w - main_menu_buttons_width / 2, 275, main_menu_buttons_width, main_menu_buttons_height, "New game", buttonPlayAction);
        m_ui.m_buttons.emplace_back(win_w - main_menu_buttons_width / 2, 330, main_menu_buttons_width, main_menu_buttons_height, "Exit", buttonPlayAction);
    }

    void Application::handleUIEvents()
    {
        SDL_Event event;
        int abs_mouse_x, abs_mouse_y;
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                m_running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&abs_mouse_x, &abs_mouse_y);
                    for (auto& button : m_ui.m_buttons) {
                        button.handleClick(abs_mouse_x, abs_mouse_y, m_current_window_state);
                    }
                }
            }
        }
    }

    void Application::handleEvents(Scene &scene, Renderer* renderer, Window *window, bool& mouseCaptured)
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
                    SDL_GetMouseState(&abs_mouse_x, &abs_mouse_y);
                    for (auto& button : m_ui.m_buttons) {
                        button.handleClick(abs_mouse_x, abs_mouse_y, m_current_window_state);
                    }

                    mouseCaptured = true;
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                }

                if (event.button.button == SDL_BUTTON_LEFT && mouseCaptured == true) {
                    renderer->drawGun(true);
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
        delete m_window;

        for (Scene* scene : m_scenes) {
            delete scene;

        }
        m_scenes.clear();
    }

} // engine

