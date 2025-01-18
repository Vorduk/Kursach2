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
        scene->addPlayer(2, 2, 0, 100);

        engine::Scene* scene2 = new engine::Scene();
        scene2->readMap("map.map");

        app.addScene(scene2);
        app.run();

    }
    catch (const engine::EngineException& e) {
        e.printInfo();
    }

    return 0;
}



