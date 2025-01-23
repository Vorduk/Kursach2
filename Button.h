#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SDL.h>
#include "Text.h"
#include <functional>

/**
 * @namespace engine
 * @brief This namespace contains classes for game engine.
 */
namespace engine {

	/**
	 * @enum WindowState
	 * @brief This enum defines the different states of the application window.
	 */
	enum WindowState {
		MENU,       ///< The menu state of the application.
		LOAD_NEW,   ///< The state for loading a new game.
		LOAD_SAVE,  ///< The state for loading a saved game.
		SAVE,       ///< The state for saving the current game.
		PLAY,       ///< The state for playing the game.
		PAUSE,      ///< The state for pausing the game.
		EXIT        ///< The state for exiting the application.
	};

	/**
	 * @class Button
	 * @brief This class represents a clickable button in the UI.
	 */
	class Button {
	public:
		Text m_text_block; ///< The text displayed on the button.
		int m_x; ///< Button x-coordinate on the screen.
		int m_y; ///< Button y-coordinate on the screen.
		int m_width; ///< Button width.
		int m_height; ///< Button height.
		std::string m_align; ///< Text alignment within the button.
		bool m_is_active; ///< Flag indicating if the button is active.
		SDL_Color m_body_color; ///< Color of the button body.
		SDL_Color m_border_color; ///< Color of the button border.
		int m_border_width; ///< Width of the button border.

		std::function<void(WindowState&)> onClick; ///< Function to call when the button is clicked.

		/**
		 * @brief Default constructor for the Button class.
		 */
		Button();

		/**
		 * @brief Parameterized constructor for the Button class.
		 * @param[in] x - The x-coordinate of the button.
		 * @param[in] y - The y-coordinate of the button.
		 * @param[in] width - The width of the button.
		 * @param[in] height - The height of the button.
		 * @param[in] text - The text to be displayed on the button.
		 * @param[in] click_handler - The function to be called on button click.
		 */
		Button(int x, int y, int width, int height, std::string text, std::function<void(WindowState&)> click_handler);

		/**
		 * @brief Handle button click event.
		 * @param[in] mouseX - The x-coordinate of the mouse on the screen.
		 * @param[in] mouseY - The y-coordinate of the mouse on the screen.
		 * @param[in,out] state - The current application window state to be modified.
		 */
		void handleClick(int mouseX, int mouseY, WindowState& state);

		/**
		 * @brief Check if the mouse is over the button.
		 * @param[in] mouseX - The x-coordinate of the mouse on the screen.
		 * @param[in] mouseY - The y-coordinate of the mouse on the screen.
		 * @return True if the mouse is over the button, false otherwise.
		 */
		bool mouseOver(int mouseX, int mouseY);
	};

} // namespace engine

#endif // BUTTON_H
