#include "Application.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) // Macros.

namespace engine 
{
    /**
     * @brief Button onClick() functions.
     */
    void buttonPlayNew(WindowState& m_current_window_state)
    {
        m_current_window_state = LOAD_NEW;
    }
    void buttonSave(WindowState& m_current_window_state)
    {
        m_current_window_state = SAVE;
    }
    void buttonPlayLoad(WindowState& m_current_window_state)
    {
        m_current_window_state = LOAD_SAVE;
    }
    void buttonExit(WindowState& m_current_window_state)
    {
        m_current_window_state = EXIT;
    }
    void buttonMenu(WindowState& m_current_window_state)
    {
        m_current_window_state = MENU;
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

        Scene* scene0 = new engine::Scene();
        scene0->loadMap("map.map");
        addScene(scene0);
        Scene* scene1 = new engine::Scene();
        scene1->loadMap("save.map");
        addScene(scene1);
        Scene* cur_scene = m_scenes[0];

        const double enemyUpdateInterval = 1.0 / 20.0;
        const double animationUpdateInterval = 1.0 / 4.0;
        double lastEnemyUpdateTime = 0.0;
        double lastAnimationUpdateTime = 0.0;
        auto lastTime = std::chrono::high_resolution_clock::now();
        int fps = 0;
        
        bool mouseCaptured = false;
        SDL_SetRelativeMouseMode(SDL_FALSE);

        while (m_running) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = currentTime - lastTime;
            lastTime = currentTime;

            handleUIEvents();

            renderer->clear();

            if (m_current_window_state != PAUSE) {
                m_ui.m_buttons[3].m_is_active = false;
                m_ui.m_buttons[4].m_is_active = false;
            }
            else
            {
                m_ui.m_buttons[3].m_is_active = true;
                m_ui.m_buttons[4].m_is_active = true;
            }
            if (m_current_window_state == MENU) {
                std::array<float, 3> fog_factors = { 1.0, 1.0, 1.0 };
                renderer->loadTexture("menu_bg", "textures/menu_bg.jpg");
                renderer->drawTexture("menu_bg", 0, 0, m_window->getWidth(), m_window->getHeight(), 0, 0, 800, 600, false, false, fog_factors);
                renderer->drawUI(m_ui);
            }
            else if (m_current_window_state == LOAD_NEW) {
                cur_scene = m_scenes[0];
                renderer->loadTexturesFromScene(*cur_scene);
                m_current_window_state = PLAY;
                mouseCaptured = true;
                SDL_SetRelativeMouseMode(SDL_TRUE);
            }
            else if (m_current_window_state == LOAD_SAVE) {
                cur_scene = m_scenes[1];
                renderer->loadTexturesFromScene(*cur_scene);
                m_current_window_state = PLAY;
                mouseCaptured = true;
                SDL_SetRelativeMouseMode(SDL_TRUE);
            }
            else if (m_current_window_state == PLAY) {
                disableUI();
                
                cur_scene->getPlayer().setPlayerPrevX();
                cur_scene->getPlayer().setPlayerPrevY(); 
                

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

                renderer->renderSceneDDA(cur_scene);
                renderer->drawGun(false);
                handleEvents(*cur_scene, renderer, m_window, mouseCaptured);
                cur_scene->processPlayerCollision();
                renderer->drawText("arial", "FPS:" + std::to_string(fps), 5, 5, SDL_Color({ 255, 255, 255, 255 }));
                renderer->drawText("arial", "Health: " + std::to_string(cur_scene->getPlayer().getPlayerHealth()), 5, 30, SDL_Color({ 255, 255, 255, 255 }));
                renderer->drawText("arial", "Enemies remain: " + std::to_string(cur_scene->getEnemyCount()), 5, 55, SDL_Color({ 255, 255, 255, 255 }));
            }
            else if (m_current_window_state == PAUSE) {
                reviveUI();
                renderer->renderSceneDDA(cur_scene);
                renderer->drawGun(false);
                renderer->drawUI(m_ui);
                handleEvents(*cur_scene, renderer, m_window, mouseCaptured);
            }
            else if (m_current_window_state == SAVE) {
                cur_scene->saveMap("save.map");
                m_current_window_state = PAUSE;
            }
            else if (m_current_window_state == EXIT) {
                m_running = false;
            }

            renderer->present();

            if (cur_scene->getPlayer().getPlayerHealth() <= 0) {
                m_current_window_state = MENU;
            }
        }
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
        // 0
        m_ui.m_buttons.emplace_back(win_w - main_menu_buttons_width/2, 220, main_menu_buttons_width, main_menu_buttons_height, "Continue from last save", buttonPlayLoad);
        
        // 1
        m_ui.m_buttons.emplace_back(win_w - main_menu_buttons_width / 2, 275, main_menu_buttons_width, main_menu_buttons_height, "New game", buttonPlayNew);
        
        // 2
        m_ui.m_buttons.emplace_back(win_w - main_menu_buttons_width / 2, 330, main_menu_buttons_width, main_menu_buttons_height, "Exit game", buttonExit);

        //3
        m_ui.m_buttons.emplace_back(win_w - main_menu_buttons_width / 2, 385, main_menu_buttons_width, main_menu_buttons_height, "Exit to menu", buttonMenu);
        m_ui.m_buttons[3].m_is_active = false;

        // 4
        m_ui.m_buttons.emplace_back(win_w - main_menu_buttons_width / 2, 440, main_menu_buttons_width, main_menu_buttons_height, "Save", buttonSave);
        m_ui.m_buttons[4].m_is_active = false;
    }

    void Application::disableUI()
    {
        for (Button& button : m_ui.m_buttons) { 
            button.m_is_active = false;
        }
        for (Text& text : m_ui.m_texts) { 
            text.m_is_active = false;
        }
    }

    void Application::reviveUI()
    {
        for (Button& button : m_ui.m_buttons) {
            button.m_is_active = true;
        }
        for (Text& text : m_ui.m_texts) {
            text.m_is_active = true;
        }
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

                m_current_window_state = PAUSE;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {

                SDL_GetMouseState(&abs_mouse_x, &abs_mouse_y);
                bool is_button = false;
                for (auto& button : m_ui.m_buttons) {
                    is_button = (is_button || button.mouseOver(abs_mouse_x, abs_mouse_y));
                    button.handleClick(abs_mouse_x, abs_mouse_y, m_current_window_state);
                }

                if (event.button.button == SDL_BUTTON_LEFT && mouseCaptured == false && !is_button) {

                    mouseCaptured = true;
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                    m_current_window_state = PLAY;
                }

                if (event.button.button == SDL_BUTTON_LEFT && mouseCaptured == true && !is_button) {
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

