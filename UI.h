#ifndef UI_H
#define UI_H

#include "Text.h"
#include "Button.h"
#include <vector>

namespace engine {

    /**
     * @class UI
     * @brief Represents a user interface that manages buttons and text blocks.
     */
    class UI
    {
    public:
        std::vector<Button> m_buttons; ///< List of buttons in the UI.
        std::vector<Text> m_texts;      ///< List of text blocks in the UI.

        /**
         * @brief Default constructor for the UI class.
         * Initializes an empty user interface.
         */
        UI();

        /**
         * @brief Default destructor for the UI class.
         * Cleans up the UI resources.
         */
        ~UI() = default;

        /**
         * @brief Adds a button to the UI.
         * @param[in] button - The button to be added.
         */
        void addButton(const Button& button);

        /**
         * @brief Adds a text block to the UI.
         * @param[in] text - The text block to be added.
         */
        void addTextBlock(const Text& text);
    };

} // engine

#endif // UI_H
