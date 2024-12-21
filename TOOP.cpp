#include <iostream>
#include <exception>
#include <string>
#include <SDL.h>

#include "Window.h"
#include "EngineException.h"

int main(int argc, char* argv[]) {
    

    try {
        engine::Window* w1 = new engine::Window(800, 600, "okno");
        //engine::Window* w2 = new engine::Window(800, 600, "okno");

        // Основной цикл
        bool running = true;
        SDL_Event event;

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }

        }
    }
    catch (const engine::EngineException& e) {
        e.printInfo();
    }

    return 0;
}


//int main(int argc, char* argv[]) {
//    // Инициализация SDL
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cerr << "Не удалось инициализировать SDL: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    // Создание окна
//    SDL_Window* window = SDL_CreateWindow("Пример SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
//    if (!window) {
//        std::cerr << "Не удалось создать окно: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return 1;
//    }
//
//    // Основной цикл
//    bool running = true;
//    SDL_Event event;
//
//    while (running) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//        }
//
//        // Здесь можно добавить код для отрисовки и обновления
//    }
//
//    // Очистка ресурсов
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    return 0;
//}
