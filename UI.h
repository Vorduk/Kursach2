#pragma once

//#ifndef UI_H
//#define UI_H

#include "Text.h"
#include "Button.h"
#include <vector>

namespace engine {

	class UI
	{
	public:
		std::vector<Button> m_buttons;
		std::vector<Text> m_texts;

		UI();
		~UI() = default;

		void addButton(const Button& button);
		void addTextBlock(const Text& text);
	};

} // engine

//#endif // UI_H
