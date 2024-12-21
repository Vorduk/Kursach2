#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <stdexcept>
#include <SDL.h>
#include "EngineException.h"

typedef unsigned int uint;

namespace engine {

	/**
	 * @brief Window class.
	 */
	class Window
	{
	private:
		uint m_width; // Window width.
		uint m_height; // Window height.
		std::string m_name; // Window caption.
		SDL_Window* m_window; // Window ptr.
	public:
		Window(uint width, uint height, std::string name); // Constructor.
		~Window(); // Destructor.
		void init(); // SDL initialization (SDL_INIT_VIDEO).
	};

} // engine

#endif WINDOW_H





