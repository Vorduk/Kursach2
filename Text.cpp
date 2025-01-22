#include "Text.h"

namespace engine {

	Text::Text() : m_x(0), m_y(0), m_text("Text"), m_is_active(true), m_font("arial"), m_color(SDL_Color({ 0, 0, 0, 255 })) {}

	Text::Text(int x, int y, std::string text) : m_x(x), m_y(y), m_text(text), m_is_active(true), m_font("arial"), m_color(SDL_Color({ 0, 0, 0, 255 })) {}

} // engine
