#ifndef ENGINE_EXCEPTION_H
#define ENGINE_EXCEPTION_H

#include <iostream>
#include <exception>

namespace engine {

    /**
     * @brief Custom exception.
     */
    class EngineException : public std::exception
    {
    private:
        std::string m_message; ///< Current message.
        const char* m_file; ///< Current file.
        int m_line; ///< Current line.
        const char* m_function; ///< Current function
    public:

        /**
         * @brief Constructor.
         * @param[in] message -Current message.
         * @param[in] file -Current file.
         * @param[in] line -Current line.
         * @param[in] function -Current function.
         */
        EngineException(const std::string& message, const char* file, int line, const char* function)
            : m_message(message), m_file(file), m_line(line), m_function(function) {}

        /**
         * @brief What() override.
         */
        const char* what() const noexcept override {
            return m_message.c_str();
        }

        /**
         * @brief Full information output.
         */
        void printInfo() const {
            std::cerr << "[ERROR]: "
                << m_message
                << " at "
                << m_file
                << ", line " << m_line
                << ", " << m_function << "()"
                << "\n";
        }
    };

} // engine

#endif ENGINE_EXCEPTION_H