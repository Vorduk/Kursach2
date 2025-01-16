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
        app.addWindow(800, 600, "okno");

        engine::Scene* scene = new engine::Scene();
        scene->addCamera(0, 0, 0, 40, 100);
        scene->addPlayer(1, 1, 45, 100);


        app.addScene(scene);
        app.run();

    }
    catch (const engine::EngineException& e) {
        e.printInfo();
    }

    return 0;
}



