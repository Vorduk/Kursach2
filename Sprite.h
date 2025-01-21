#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>

struct Sprite {
    double m_x;                     ///< Cord x
    double m_y;                     ///< Cord y
    int m_height;                   ///< Height
    int m_width;                    ///< Width
    std::vector<std::string> m_texture_ids; ///< Textures id array
    int m_speed;                    ///< speed

    Sprite() : m_x(0.0), m_y(0.0), m_height(0), m_width(0), m_speed(0) {}

    Sprite(double x, double y, int height, int width, const std::vector<std::string>& texture_ids, int speed)
        : m_x(x), m_y(y), m_height(height), m_width(width), m_texture_ids(texture_ids), m_speed(speed) {}
};

#endif // SPRITE_H

