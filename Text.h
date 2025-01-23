#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL.h>

namespace engine {

    /**
     * @class Text
     * @brief Represents a text object that can be rendered on the screen.
     */
    class Text {
    public:
        int m_x; ///< X-coordinate - The x position of the text on the screen.
        int m_y; ///< Y-coordinate - The y position of the text on the screen.
        std::string m_text; ///< Text content - The string content of the text.
        bool m_is_active; ///< Active state - Indicates whether the text is currently active.
        std::string m_font; ///< Font identifier - The name or path of the font used for rendering the text.
        SDL_Color m_color; ///< Text color - The color of the text.

        /**
         * @brief Default constructor for the Text class.
         * Initializes the text object with default values.
         */
        Text();

        /**
         * @brief Parameterized constructor for the Text class.
         * @param[in] x - The x-coordinate of the text.
         * @param[in] y - The y-coordinate of the text.
         * @param[in] text - The string content of the text.
         */
        Text(int x, int y, std::string text);
    };

} // namespace engine

#endif // TEXT_H
