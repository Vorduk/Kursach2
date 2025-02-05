#include "Button.h"

namespace engine {

	Button::Button() :
		m_text_block(Text(0, 0, "text")),
		m_x(0),
		m_y(0),
		m_width(100),
		m_height(20),
		m_align("center"),
		m_is_active(true),
		m_body_color(SDL_Color({ 200, 200, 200, 255 })),
		m_border_color(SDL_Color({ 50, 50, 50, 255 })),
		m_border_width(1),
		onClick(nullptr)
	{}

	Button::Button(int x, int y, int width, int height, std::string text, std::function<void(WindowState&)> click_handler) :
		m_text_block(Text(x, y, text)),
		m_x(x),
		m_y(y),
		m_width(width),
		m_height(height),
		m_align("center"),
		m_is_active(true),
		m_body_color(SDL_Color({ 200, 200, 200, 255 })),
		m_border_color(SDL_Color({ 50, 50, 50, 255 })),
		m_border_width(1),
		onClick(click_handler)
	{}

	void Button::handleClick(int mouseX, int mouseY, WindowState& state)
	{
		if (mouseOver(mouseX, mouseY)) {
			if (onClick) {
				onClick(state);
			}
		}
	}

	bool Button::mouseOver(int mouseX, int mouseY)
	{
		return (m_is_active && mouseX >= m_x && mouseX <= m_x + m_width && mouseY >= m_y && mouseY <= m_y + m_height);
	}

} // engine