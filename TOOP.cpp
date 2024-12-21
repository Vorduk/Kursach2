#include <iostream>
#include <exception>
#include <string>
#include <SDL.h>

#include "Application.h"
#include "EngineException.h"

int main(int argc, char* argv[]) {
    

    try {
        engine::Application* app = new engine::Application();
        app->createWindow(800, 600, "okno");
        app->run();


    }
    catch (const engine::EngineException& e) {
        e.printInfo();
    }

    return 0;
}


