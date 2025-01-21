#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <chrono>
#include "Sprite.h"

typedef unsigned int uint;

namespace engine {

    class Enemy {
    protected:
        double m_enemy_x;
        double m_enemy_y;
        double m_velocity;
        int m_health;
        std::string m_enemy_texture_id;
        std::string m_enemy_dead_texture_id;
        int m_death_counter;
        bool m_is_dead = false;
        double m_attack_range;
        int m_attack_damage;

        Sprite m_sprite;

    public:
        Enemy(double x, double y, int health, double velocity, double attack_range, int attack_damage);
        virtual ~Enemy();

        virtual void attack(uint* target_health) = 0;

        double getX() const;
        double getY() const;
        int getHealth() const;
        void setPosition(double x, double y);
        void takeDamage(int damage);
        double getVelocity();
        void setTextureId(std::string texture_id);
        std::string getTextureId();
        void setDeadTextureId(std::string enemy_dead_texture_id);
        std::string getDeadTextureId();
        void setVelocity(int velocity);
        void die();
        bool isDead() const;
        int getDeathCounter() const;
        void addCounter();

        Sprite m_enemy_sprite;
        Sprite getSprite();
        void SetSprite();
        Sprite m_dead_enemy_sprite;
    };

    class Zombie : public Enemy {
    public:
        Zombie(double x, double y, int health, double velocity, double attack_range, int attack_damage);
        void attack(uint* target_health) override;
    };

    class Alien : public Enemy {
    public:
        Alien(double x, double y, int health, double velocity, double attack_range, int attack_damage);
        void attack(uint* target_health) override;
    };

} // namespace engine

#endif // ENEMY_H
