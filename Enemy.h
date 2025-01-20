#ifndef ENEMY_H
#define ENEMY_H

#include <string>

namespace engine {

    class Enemy {
    protected:
        double m_enemy_x;
        double m_enemy_y;
        double m_velocity;
        int m_health;
        std::string m_enemy_texture_id;

    public:
        Enemy(double x, double y, int health, double velocity);
        virtual ~Enemy();

        virtual void update() = 0;
        virtual void attack() = 0;

        double getX() const;
        double getY() const;
        int getHealth() const;
        void setPosition(double x, double y);
        void takeDamage(int damage);
        double getVelocity();
        void setTextureId(std::string texture_id);
        std::string getTextureId();
    };

    class Zombie : public Enemy {
    public:
        Zombie(double x, double y, int health, double velocity);
        void update() override; 
        void attack() override;
    };

    class Alien : public Enemy {
    public:
        Alien(double x, double y, int health, double velocity);
        void update() override;
        void attack() override; 
    };

} // namespace engine

#endif // ENEMY_H
