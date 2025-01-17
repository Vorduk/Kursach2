#include "Camera.h"

namespace engine
{

    Camera::Camera() {
        m_camera_y = 0;
        m_camera_x = 0;
        m_camera_angle = 0;
        m_fov_c = 40;
        m_fov = (m_fov_c / 180 * M_PI);
        m_render_distance = 200;
    }

    Camera::Camera(double camera_y, double camera_x, double camera_angle, double fov_c, int render_distance) {
        m_camera_y = camera_y;
        m_camera_x = camera_x;
        m_camera_angle = camera_angle;
        m_fov_c = fov_c;
        m_fov = (fov_c / 180 * M_PI);
        m_render_distance = render_distance;
    }

    Camera::~Camera() {

    };

    void Camera::setCameraCoords(double camera_y, double camera_x) {
        m_camera_y = camera_y;
        m_camera_x = camera_x;
    }
    void Camera::setCameraY(double camera_y) {
        m_camera_y = camera_y;
    }
    double Camera::getCameraY() {
        return m_camera_y;
    }
    void Camera::setCameraX(double camera_x) {
        m_camera_x = camera_x;
    }
    double Camera::getCameraX() {
        return m_camera_x;
    }
    void Camera::setCameraAngle(double camera_angle) {
        m_camera_angle = camera_angle;
    }
    double Camera::getCameraAngle() {
        return m_camera_angle;
    }
    void Camera::setFovC(double fov_c) {
        m_fov_c = fov_c;
    }
    double Camera::getFovC() {
        return m_fov_c;
    }
    void Camera::setFov(double fov) {
        m_fov = fov;
    }
    double Camera::getFov() {
        return m_fov;
    }
    void Camera::setRenderDistance(int render_distance) {
        m_render_distance = render_distance;
    }
    int Camera::getRenderDistance() {
        return m_render_distance;
    }

    void Camera::synchronizeWithPlayer(Player& player)
    {
        setCameraCoords(player.getPlayerY(), player.getPlayerX());
        m_camera_angle = player.getPlayerAngle();
    }

} // engine
