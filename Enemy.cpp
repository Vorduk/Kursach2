#include "enemy.h"
#include <iostream>


engine::Enemy::Enemy(double x, double y, int health, double velocity, double attack_range, int attack_damage)
    : m_enemy_x(x), m_enemy_y(y), m_health(health), m_velocity(velocity), m_is_dead(false), m_death_counter(0), m_attack_range(attack_range), m_attack_damage(attack_damage) {}

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

void engine::Enemy::setVelocity(int velocity)
{
    m_velocity = velocity;
}

void engine::Enemy::die()
{
    m_is_dead = true;
    m_death_counter = 0;
}

int engine::Enemy::getDeathCounter() const
{
    return m_death_counter;
}

Sprite engine::Enemy::getSprite()
{
    return m_sprite;
}

void engine::Enemy::addCounter()
{
    m_death_counter += 1;
}

bool engine::Enemy::isDead() const 
{
    return m_is_dead;
}

void engine::Enemy::setDeadTextureId(std::string enemy_dead_texture_id)
{
    m_enemy_dead_texture_id = enemy_dead_texture_id;
}

std::string engine::Enemy::getDeadTextureId()
{
    return m_enemy_dead_texture_id;
}

engine::Zombie::Zombie(double x, double y, int health, double velocity, double attack_range, int attack_damage)
    : Enemy(x, y, health, velocity, attack_range, attack_damage) {}

void engine::Zombie::attack(uint* target_health) {
    std::cout << "Zombie attacks!" << std::endl;
    if (target_health != nullptr) {
        *target_health -= m_attack_damage;
        if (*target_health < 0) {
            *target_health = 0;
        }
    }
}

engine::Alien::Alien(double x, double y, int health, double velocity, double attack_range, int attack_damage)
    : Enemy(x, y, health, velocity, attack_range, attack_damage) {}

void engine::Alien::attack(uint* target_health) {
    std::cout << "Alien attacks!" << std::endl;
    if (target_health != nullptr) {
        *target_health -= m_attack_damage;
        if (*target_health < 0) {
            *target_health = 0;
        }
    } 
}
