#ifndef CAMERA_H
#define CAMERA_H

#include <corecrt_math_defines.h>
#include "Player.h"

namespace engine
{
    class Camera {
    private:
        double m_camera_y;
        double m_camera_x;
        double m_camera_angle;
        double m_fov_c;
        double m_fov;
        int m_render_distance;
    public:
        Camera();
        Camera(double camera_y, double camera_x, double camera_angle, double fov_c, int render_distance);
        ~Camera();
        void setCameraCoords(double camera_y, double camera_x);
        void setCameraY(double camera_y);
        double getCameraY();
        void setCameraX(double camera_x);
        double getCameraX();
        void setCameraAngle(double camera_angle);
        double getCameraAngle();
        void setFovC(double fov_c);
        double getFovC();
        void setFov(double fov);
        double getFov();
        void setRenderDistance(int render_distance);
        int getRenderDistance();

        /**
         * @brief Synchronizes camera with player.
         * The camera is not synchronized automatically to be able to control it separately
         */
        void synchronizeWithPlayer(Player& player);
    };
}

#endif CAMERA_H

