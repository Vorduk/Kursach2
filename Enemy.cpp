#include "enemy.h"
#include <iostream>


engine::Enemy::Enemy(double x, double y, int health, double velocity)
    : m_enemy_x(x), m_enemy_y(y), m_health(health), m_velocity(velocity) {}

engine::Enemy::~Enemy() {}

double engine::Enemy::getX() const {
    return m_enemy_x;
}

double engine::Enemy::getY() const {
    return m_enemy_y;
}

int engine::Enemy::getHealth() const {
    return m_health;
}

void engine::Enemy::setPosition(double x, double y) {
    m_enemy_x = x;
    m_enemy_y = y;
}

void engine::Enemy::takeDamage(int damage) {
    m_health -= damage;
    if (m_health < 0) {
        m_health = 0; 
    }
}

double engine::Enemy::getVelocity()
{
    return m_velocity;
}

void engine::Enemy::setTextureId(std::string texture_id)
{
    m_enemy_texture_id = texture_id;
}

std::string engine::Enemy::getTextureId()
{
    return m_enemy_texture_id;
}


engine::Zombie::Zombie(double x, double y, int health, double velocity)
    : Enemy(x, y, health, velocity) {}

void engine::Zombie::update() {
    std::cout << "Zombie at (" << m_enemy_x << ", " << m_enemy_y << ") is updating." << std::endl;
}

void engine::Zombie::attack() {
    std::cout << "Zombie attacks!" << std::endl;
}


engine::Alien::Alien(double x, double y, int health, double velocity)
    : Enemy(x, y, health, velocity) {}

void engine::Alien::update() {
    std::cout << "Alien at (" << m_enemy_x << ", " << m_enemy_y << ") is updating." << std::endl;
}

void engine::Alien::attack() {
    std::cout << "Alien attacks!" << std::endl;
}
