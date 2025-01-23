#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>

/**
 * @struct Sprite
 * @brief Represents a sprite with position, texture, and animation frames.
 */
struct Sprite {
    double m_x;                     ///< Cord x - The x-coordinate of the sprite.
    double m_y;                     ///< Cord y - The y-coordinate of the sprite.
    std::string m_texture_id;       ///< Textures id - The identifier for the sprite's texture.
    int m_frames;                   ///< Number of frames - The total number of animation frames.
    int m_current_frame;            ///< Current frame - The index of the currently displayed frame.

    /**
     * @brief Default constructor for the Sprite struct.
     * Initializes the sprite at the origin (0, 0) with one frame.
     */
    Sprite() : m_x(0.0), m_y(0.0), m_frames(1), m_current_frame(0) {}

    /**
     * @brief Parameterized constructor for the Sprite struct.
     * @param[in] x - The x coordinate of the sprite.
     * @param[in] y - The y coordinate of the sprite.
     * @param[in] frames - The total number of animation frames.
     * @param[in] start_frame - The starting frame index for the sprite animation.
     * @param[in] texture_id - The identifier for the sprite's texture.
     */
    Sprite(double x, double y, int frames, int start_frame, std::string texture_id)
        : m_x(x), m_y(y), m_frames(frames), m_current_frame(start_frame), m_texture_id(texture_id) {}
};

#endif // SPRITE_H
