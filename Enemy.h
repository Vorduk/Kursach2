#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <chrono>
#include "Sprite.h"
#include <corecrt_math_defines.h>

typedef unsigned int uint;



namespace engine {

    enum EnemyBehavior {
        IDLE,    
        ACTIVE,  
        DEAD    
    };

    class Enemy {
    protected:
        double m_enemy_x;
        double m_enemy_y;
        double m_velocity;
        int m_health;
        int m_death_counter;
        double m_attack_range;
        int m_attack_damage;
        Sprite m_enemy_sprite;
        Sprite m_dead_enemy_sprite;
        EnemyBehavior m_behavior;
        double m_target_x;
        double m_target_y;

    public:
        Enemy(double x, double y, int health, double velocity, double attack_range, int attack_damage, EnemyBehavior enemy_behavior);
        virtual ~Enemy();

        virtual void attack(uint* target_health) = 0;

        double getX() const;
        double getY() const;
        int getHealth() const;
        void setPosition(double x, double y);
        void takeDamage(int damage);
        double getVelocity();
        void setVelocity(int velocity);
        void die();
        bool isDead() const;
        int getDeathCounter() const;
        void addCounter();
        
        Sprite& getEnemySprite();
        void SetEnemySprite(Sprite enemy_sprite);
        
        Sprite& getDeadEnemySprite();
        void SetDeadEnemySprite(Sprite dead_enemy_sprite);

        void update(uint* target_health, double target_x, double target_y, std::vector<std::vector<int>> obstacles);

        double raycastObstacles(double target_x, double target_y, std::vector<std::vector<int>> obstacles);
    };

    class Zombie : public Enemy {
    public:
        Zombie(double x, double y, int health, double velocity, double attack_range, int attack_damage, EnemyBehavior enemy_behavior);
        void attack(uint* target_health) override;
    };

    class Alien : public Enemy {
    public:
        Alien(double x, double y, int health, double velocity, double attack_range, int attack_damage, EnemyBehavior enemy_behavior);
        void attack(uint* target_health) override;
    };

} // namespace engine

#endif // ENEMY_H
