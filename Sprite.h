#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>

struct Sprite {
    double m_x;                     ///< Cord x
    double m_y;                     ///< Cord y
    std::string m_texture_id; ///< Textures id array
    int m_frames;
    int m_current_frame;
    int m_speed;                    ///< speed

    Sprite() : m_x(0.0), m_y(0.0), m_frames(1), m_current_frame(0), m_speed(0) {}

    Sprite(double x, double y, int frames, int start_frame, std::string texture_id, int speed)
        : m_x(x), m_y(y), m_texture_id(texture_id), m_frames (frames), m_current_frame(start_frame), m_speed(speed) {}
};

#endif // SPRITE_H

