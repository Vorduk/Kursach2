#include <iostream>
#include <exception>
#include <string>
#include <SDL.h>

#include "Application.h"
#include "EngineException.h"

int main(int argc, char* argv[]) {
    
    try {
        engine::Application app = engine::Application();
        app.addWindow(800, 600, "okno");
        app.addScene();
        app.run();

    }
    catch (const engine::EngineException& e) {
        e.printInfo();
    }

    return 0;
}


