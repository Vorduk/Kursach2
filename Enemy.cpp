#include "enemy.h"
#include <iostream>


engine::Enemy::Enemy(double x, double y, int health, double velocity, double attack_range, int attack_damage, EnemyBehavior enemy_behavior)
    : m_enemy_x(x), m_enemy_y(y), m_health(health), m_velocity(velocity), m_death_counter(0), m_attack_range(attack_range), m_attack_damage(attack_damage), m_behavior(enemy_behavior){}

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

void engine::Enemy::setVelocity(int velocity)
{
    m_velocity = velocity;
}

void engine::Enemy::die()
{
    m_behavior = DEAD;
    m_death_counter = 0;
}

int engine::Enemy::getDeathCounter() const
{
    return m_death_counter;
}

void engine::Enemy::addCounter()
{
    m_death_counter += 1;
}

Sprite& engine::Enemy::getEnemySprite()
{
    return m_enemy_sprite;
}

void engine::Enemy::SetEnemySprite(Sprite enemy_sprite)
{
    m_enemy_sprite = enemy_sprite;
}

Sprite& engine::Enemy::getDeadEnemySprite()
{
    return m_dead_enemy_sprite;
}

void engine::Enemy::SetDeadEnemySprite(Sprite dead_enemy_sprite)
{
    m_dead_enemy_sprite = dead_enemy_sprite;
}

bool engine::Enemy::isDead() const 
{
    return (m_behavior == DEAD);
}

engine::Zombie::Zombie(double x, double y, int health, double velocity, double attack_range, int attack_damage, EnemyBehavior enemy_behavior)
    : Enemy(x, y, health, velocity, attack_range, attack_damage, enemy_behavior) {}

void engine::Zombie::attack(uint* target_health) {
    std::cout << "Zombie attacks!" << std::endl;
    if (target_health != nullptr) {
        *target_health -= m_attack_damage;
        if (*target_health < 0) {
            *target_health = 0;
        }
    }
}

engine::Alien::Alien(double x, double y, int health, double velocity, double attack_range, int attack_damage, EnemyBehavior enemy_behavior)
    : Enemy(x, y, health, velocity, attack_range, attack_damage, enemy_behavior) {}

void engine::Alien::attack(uint* target_health) {
    std::cout << "Alien attacks!" << std::endl;
    if (target_health != nullptr) {
        *target_health -= m_attack_damage;
        if (*target_health < 0) {
            *target_health = 0;
        }
    } 
}
