#include "enemy.h"
#include <iostream>

namespace engine {
    Enemy::Enemy(double x, double y, int health, double velocity, double attack_range, int attack_damage, EnemyBehavior enemy_behavior)
        : m_enemy_x(x), m_enemy_y(y), m_health(health), m_velocity(velocity), m_death_counter(0), m_attack_range(attack_range), m_attack_damage(attack_damage), m_behavior(enemy_behavior){}

    Enemy::~Enemy() {}

    double Enemy::getX() const {
        return m_enemy_x;
    }

    double Enemy::getY() const {
        return m_enemy_y;
    }

    int Enemy::getHealth() const {
        return m_health;
    }

    void Enemy::setPosition(double x, double y) {
        m_enemy_x = x;
        m_enemy_y = y;
    }

    void Enemy::takeDamage(int damage) {
        m_health -= damage;
        if (m_health < 0) {
            m_health = 0; 
        }
    }

    double Enemy::getVelocity()
    {
        return m_velocity;
    }

    void Enemy::setVelocity(int velocity)
    {
        m_velocity = velocity;
    }

    void Enemy::die()
    {
        m_dead_enemy_sprite.m_x = m_enemy_x;
        m_dead_enemy_sprite.m_y = m_enemy_y;
        m_enemy_sprite = m_dead_enemy_sprite;
        m_velocity = 0;
        m_behavior = DEAD;
        m_death_counter = 0;
    }

    int Enemy::getDeathCounter() const
    {
        return m_death_counter;
    }

    void Enemy::addCounter()
    {
        m_death_counter += 1;
    }

    Sprite& Enemy::getEnemySprite()
    {
        return m_enemy_sprite;
    }

    void Enemy::SetEnemySprite(Sprite enemy_sprite)
    {
        m_enemy_sprite = enemy_sprite;
    }

    Sprite& Enemy::getDeadEnemySprite()
    {
        return m_dead_enemy_sprite;
    }

    void Enemy::SetDeadEnemySprite(Sprite dead_enemy_sprite)
    {
        m_dead_enemy_sprite = dead_enemy_sprite;
    }

    void Enemy::update(uint* target_health, double target_x, double target_y, std::vector<std::vector<int>> obstacles)
    {
        if (isDead()) {
            addCounter();
            return;
        }

        if (m_health <= 0 && !isDead()) {
            die();
            return;
        }

        double dx = target_x - m_enemy_x;
        double dy = target_y - m_enemy_y;
        double distance = std::sqrt(dx * dx + dy * dy);

        double cast = raycastObstacles(target_x, target_y, obstacles);

        if (distance < 20 && (cast >= distance || cast == -1)) {
            m_behavior = ACTIVE;
        }
        else {
            m_behavior = IDLE;
        }

        if (m_behavior == ACTIVE)
        {
            if (distance > 0.2) {
                // Normalize
                dx = dx / distance;
                dy = dy / distance;

                // Get new cords
                double newEnemyX = m_enemy_x + dx * m_velocity;
                double newEnemyY = m_enemy_y + dy * m_velocity;

                int gridX = static_cast<int>(newEnemyX);
                int gridY = static_cast<int>(newEnemyY);

                if (obstacles[gridY][gridX] == 0) {
                    m_enemy_x = newEnemyX;
                    m_enemy_y = newEnemyY;

                    m_enemy_sprite.m_x = newEnemyX;
                    m_enemy_sprite.m_y = newEnemyY;
                }

            }
            if (distance < m_attack_range) {
                attack(target_health);
            }
        }
    }

    double Enemy::raycastObstacles(double target_x, double target_y, std::vector<std::vector<int>> obstacles)
    {
        //DDA raycast
         
        int map_check_x = m_enemy_x;
        int map_check_y = m_enemy_y;

        int hit = 0;
        int hit_door = 0;

        float ray_angle = atan2(target_y - m_enemy_y, target_x - m_enemy_x);

        float dx = cos(ray_angle);
        float dy = sin(ray_angle);

        double unit_step_size_x = sqrt(1 + (dy / dx) * (dy / dx));
        double unit_step_size_y = sqrt(1 + (dx / dy) * (dx / dy));

        double ray_length_x;
        double ray_length_y;

        double step_x;
        double step_y;

        if (dx < 0)
        {
            step_x = -1;
            ray_length_x = (m_enemy_x - float(map_check_x)) * unit_step_size_x;
        }
        else {
            step_x = 1;
            ray_length_x = (float(map_check_x + 1) - m_enemy_x) * unit_step_size_x;
        }

        if (dy < 0)
        {
            step_y = -1;
            ray_length_y = (m_enemy_y - float(map_check_y)) * unit_step_size_y;
        }
        else {
            step_y = 1;
            ray_length_y = (float(map_check_y + 1) - m_enemy_y) * unit_step_size_y;
        }

        double dot_x;
        double dot_y;

        double cur_distance = 0.0;
        while (cur_distance < 20) {

            // walk
            if (ray_length_x < ray_length_y) {
                map_check_x += step_x;
                cur_distance = ray_length_x;
                ray_length_x += unit_step_size_x;
            }
            else {
                map_check_y += step_y;
                cur_distance = ray_length_y;
                ray_length_y += unit_step_size_y;
            }

            dot_x = m_enemy_x + dx * cur_distance;
            dot_y = m_enemy_y + dy * cur_distance;

            if (map_check_x >= 0 && map_check_x < obstacles.size() && map_check_y >= 0 && map_check_y < obstacles[0].size()) {
                hit = obstacles[map_check_y][map_check_x];
                if (hit != 0) {
                    break;
                }
            }
        }

        if (hit != 0) {
            return cur_distance;
        }
        else return -1.0;
    }

    bool engine::Enemy::isDead() const 
    {
        return (m_behavior == DEAD);
    }

    engine::Zombie::Zombie(double x, double y, int health, EnemyBehavior enemy_behavior)
        : Enemy(x, y, health, 0.1, 1, 1, enemy_behavior) {}

    void engine::Zombie::attack(uint* target_health) {
        if (target_health != nullptr) {
            *target_health -= m_attack_damage;
            if (*target_health < 0) {
                *target_health = 0;
            }
        }
    }

    std::string Zombie::getEnemyType() const
    {
        return "Zombie";
    }

    engine::Alien::Alien(double x, double y, int health, EnemyBehavior enemy_behavior)
        : Enemy(x, y, health, 0.13, 1.2, 3, enemy_behavior) {}

    void engine::Alien::attack(uint* target_health) {
        if (target_health != nullptr) {
            *target_health -= m_attack_damage;
            if (*target_health < 0) {
                *target_health = 0;
            }
        } 
    }

    std::string Alien::getEnemyType() const
    {
        return "Alien";
    }


} // engine

