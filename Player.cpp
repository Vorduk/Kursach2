#include "Player.h"

namespace engine
{

    Player::Player()
        : m_player_health(100),
        m_player_y(0),
        m_player_x(0),
        m_player_angle(0),
        m_player_prev_y(0),
        m_player_prev_x(0)
    {}

    Player::Player(double player_y, double player_x, double player_angle, uint player_health)
        : m_player_health(player_health),
        m_player_y(player_y),
        m_player_x(player_x),
        m_player_angle(player_angle),
        m_player_prev_y(player_x),
        m_player_prev_x(player_x)
    {}

    Player::~Player() {

    };
    
    void Player::setPlayerCoords(double player_y, double player_x) {
        m_player_y = player_y;
        m_player_x = player_x;
    }
    void Player::setPlayerY(double player_y) {
        m_player_y = player_y;
    }
    double Player::getPlayerY() {
        return m_player_y;
    }
    void Player::setPlayerX(double player_x) {
        m_player_x = player_x;
    }
    double Player::getPlayerX() {
        return m_player_x;
    }
    void Player::setPlayerPrevY() {
        m_player_prev_y = m_player_y;
    }
    void Player::setPlayerPrevX() {
        m_player_prev_x = m_player_x;
    }
    void Player::setPlayerAngle(double player_angle) {
        m_player_angle = player_angle;
    }
    double Player::getPlayerAngle() {
        return m_player_angle;
    }
    void Player::setPlayerHealth(uint player_health) {
        m_player_health = player_health;
    }
    uint Player::getPlayerHealth() {
        return m_player_health;
    }
    
    void Player::movePlayer(double step) {
        m_player_x = m_player_x + step * cos(m_player_angle);
        m_player_y = m_player_y + step * sin(m_player_angle);
    }
    
    void Player::movePlayerSide(double step) {
        m_player_x = m_player_x + step * sin(m_player_angle);
        m_player_y = m_player_y - step * cos(m_player_angle);
    }
    
    void Player::movePlayerDiagonal(double step_forward, double step_side) {
        m_player_x = m_player_x + step_forward * cos(m_player_angle) + step_side * sin(m_player_angle);
        m_player_y = m_player_y + step_forward * sin(m_player_angle) - step_side * cos(m_player_angle);
    }
    
    void Player::addPlayerAngle(double value) {
        m_player_angle += value;
        if (m_player_angle > 2*M_PI) { m_player_angle = 0; }
        if (m_player_angle < 0) { m_player_angle = 2 * M_PI; }
    }

    void Player::returnBack() {
        m_player_x = m_player_prev_x;
        m_player_y = m_player_prev_y;
    }

    void Player::applyDamage(int damage) {
        m_player_health -= damage;
    }

    uint* Player::getHealthPointer()
    {
        return &m_player_health;
    }

}
