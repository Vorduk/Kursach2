#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL.h>
#include "Text.h"
#include <functional>

namespace engine {

	enum WindowState {
		MENU,
		PLAY,
		PAUSE,
		EXIT
	};

	class Button {
	public:
		Text m_text_block;
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		std::string m_align;
		bool m_is_active;
		SDL_Color m_body_color;
		SDL_Color m_border_color;
		int m_border_width;

		std::function<void(WindowState&)> onClick;

		Button();
		Button(int x, int y, int width, int height, std::string text, std::function<void(WindowState&)> click_handler);

		void handleClick(int mouseX, int mouseY, WindowState& state);
	};
}

#endif // BUTTON_H
