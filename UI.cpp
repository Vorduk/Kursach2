#include "UI.h"

namespace engine {

	UI::UI() : m_buttons(), m_texts() {}

	void UI::addButton(const Button& button)
	{
		m_buttons.push_back(button);
	}

	void UI::addTextBlock(const Text& text)
	{
		m_texts.push_back(text);
	}

} // engine