#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include <vector>
#include "Renderer.h"
#include "Scene.h"
#include <chrono>
#include "UI.h"

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
		Window* m_window; ///< app windows
		std::string m_name; ///< App name
		bool m_running; ///< Running flag
		UI m_ui; ///< User interface;
	public:
		WindowState m_current_window_state;
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
		void setWindow(uint width, uint height, const std::string& caption);

		/**
		 * @brief Creates ui.
		 */
		void addUI();

		/**
		 * @brief Disables ui.
		 */
		void disableUI();

		/**
		 * @brief Disables ui.
		 */
		void reviveUI();

		/**
		 * @brief Handles ui events, changes window state.
		 */
		void handleUIEvents();

		/**
		 * @brief Event handling.
		 */
		void handleEvents(Scene &scene, Renderer* renderer, Window* window, bool& mouseCaptured);

		/**
		 * @brief Windows vector cleaning.
		 */
		void cleanUp();
	};

} // engine

#endif // !APPLICATION_H

