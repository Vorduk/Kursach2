#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include <vector>
#include "Renderer.h"
#include "Scene.h"

typedef unsigned int uint;

/**
 * @namespace engine
 * @brief This namespace contains classes for game engine.
 */
namespace engine {
	/**
	 * @brief Application class (Main loop).
	 */
	class Application
	{
	private:
		std::vector<Scene*> m_scenes; ///< app scenes (maps)
		std::vector<Window*> m_windows; ///< app windows
		std::string m_name; ///< App name
		bool m_running; ///< Running flag
	public:
		Application();
		~Application(); 

		/**
		 * @brief Run app (Main loop).
		 * @param[in] scene_number -Scene number
		 */
		void run();

		/**
		 * @brief Creates a new window.
		 */
		void addScene(Scene* scene);

		/**
		 * @brief Creates a new window.
		 */
		void addWindow(uint width, uint height, const std::string& caption);

		/**
		 * @brief Event handling.
		 */
		void handleEvents(Player &player);

		/**
		 * @brief Windows vector cleaning.
		 */
		void cleanUp();
	};

} // engine

#endif // !APPLICATION_H

