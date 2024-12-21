#pragma once

#include "Window.h"
#include <vector>
#include "Renderer.h"

typedef unsigned int uint;

namespace engine {

	class Application
	{
	private:
		std::vector<engine::Window*> m_windows;
		std::string m_name;
		bool m_running;
	public:
		Application();
		~Application(); 

		void run(); 
		void createWindow(uint width, uint height, const std::string& caption);
		void handleEvents();
		void cleanUp();
	};

} // engine



