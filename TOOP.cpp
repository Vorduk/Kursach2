#include <iostream>
#include <exception>
#include <string>
#include <SDL.h>

#include "Application.h"
#include "EngineException.h"
#include "Scene.h"

int main(int argc, char* argv[]) {
    
    try {
        engine::Application app = engine::Application();
        app.setWindow(800, 600, "okno");

        engine::Scene* scene2 = new engine::Scene();
        scene2->loadMap("map.map");

        app.addScene(scene2);
        app.run();

    }
    catch (const engine::EngineException& e) {
        e.printInfo();
    }

    return 0;
}



