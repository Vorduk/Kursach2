#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <stdexcept>
#include <SDL.h>
#include "EngineException.h"

typedef unsigned int uint;

/**
 * @namespace engine
 * @brief This namespace contains classes for game engine.
 */
namespace engine {

	/**
	 * @brief Window class.
	 */
	class Window
	{
	private:
		uint m_width; ///< Window width (pixels).
		uint m_height; ///< Window height (pixels).
		std::string m_caption; ///< Window caption.
		SDL_Window* m_window; ///< Window ptr.

		/**
		 * @brief SDL initialization (SDL_INIT_VIDEO).
		 */
		void init();

	public:
		/**
		 * @brief Window Constructor.
		 * @param[in] width -Window width (pixels).
		 * @param[in] height -Window height (pixels).
		 * @param[in] caption -Window caption.
		 */
		Window(uint width, uint height, std::string caption);

		/**
		 * @brief Window destructor.
		 */
		~Window(); ///< Destructor.

		/**
		 * @brief Get window pointer.
		 */
		SDL_Window* getWindow();

		/**
		 * @brief Get window width in pixels.
		 */
		uint getWidth();

		/**
		 * @brief Get window height in pixels.
		 */
		uint getHeight(); 
	};

} // engine

#endif // WINDOW_H





