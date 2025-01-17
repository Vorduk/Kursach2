#ifndef CAMERA_H
#define CAMERA_H

#include <corecrt_math_defines.h>
#include "Player.h"

namespace engine
{
    class Camera {
    private:
        double m_camera_y; ///< Camera world y cord.
        double m_camera_x; ///< Camera world x cord.
        double m_camera_angle; ///< Camera world angle (radians).
        double m_fov_c; ///< Camera field of view (degrees).
        double m_fov; ///< Camera field of view (radians).
        int m_render_distance; ///< Camera render distance.
    public:
        /**
         * @brief Camera constructor.
         */
        Camera();

        /**
         * @brief Camera constructor.
         * @param[in] camera_y -Camera world y cord.
         * @param[in] camera_x -Camera world x cord.
         * @param[in] camera_angle -Camera world angle (radians).
         * @param[in] fov_c -Camera field of view (degrees).
         * @param[in] render_distance -Camera render distance.
         */
        Camera(double camera_y, double camera_x, double camera_angle, double fov_c, int render_distance);
        
        /**
         * @brief Camera destructor.
         */
        ~Camera();

        /**
         * @brief Set camera world cords.
         * @param[in] camera_y -Camera world y cord.
         * @param[in] camera_x -Camera world x cord.
         */
        void setCameraCoords(double camera_y, double camera_x);

        /**
         * @brief Set camera y cord.
         * @param[in] camera_y -Camera world y cord.
         */
        void setCameraY(double camera_y);
        double getCameraY(); ///< Get camera y cord.

        /**
         * @brief Set camera x cord.
         * @param[in] camera_x -Camera world x cord.
         */
        void setCameraX(double camera_x);
        double getCameraX(); ///< Get camera x cord.

        /**
         * @brief Set camera angle.
         * @param[in] camera_angle -Camera angle.
         */
        void setCameraAngle(double camera_angle);
        double getCameraAngle(); ///< Get camera angle (degrees).

        /**
         * @brief Set camera field of view (degrees).
         * @param[in] fov_c -Camera field of view (degrees).
         */
        void setFovC(double fov_c);
        double getFovC(); ///< Get camera field of view (degrees).

        /**
         * @brief Set camera field of view (radians).
         * @param[in] fov -Camera field of view (radians).
         */
        void setFov(double fov);
        double getFov(); ///< Get camera field of view (radians).

        /**
         * @brief Set camera render distance.
         * @param[in] render_distance -Camera render distance.
         */
        void setRenderDistance(int render_distance);
        int getRenderDistance(); ///< Get camera render distance.

        /**
         * @brief Synchronizes camera with player.
         * The camera is not synchronized automatically to be able to control it separately
         */
        void synchronizeWithPlayer(Player& player);
    };

} // engine

#endif // CAMERA_H

