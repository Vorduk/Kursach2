#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL.h>

namespace engine {

	class Text {
	public:
		int m_x;
		int m_y;
		std::string m_text;
		bool m_is_active;
		std::string m_font;
		SDL_Color m_color;

		Text();
		Text(int x, int y, std::string text);
	};
}

#endif // UI_H