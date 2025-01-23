#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <chrono>
#include "Sprite.h"
#include <corecrt_math_defines.h>

typedef unsigned int uint;

/**
 * @namespace engine
 * @brief This namespace contains classes for game engine.
 */
namespace engine {

    /**
     * @enum EnemyBehavior
     * @brief This enum defines the possible behaviors of an enemy.
     */
    enum EnemyBehavior {
        IDLE,    ///< The enemy is idle and not moving.
        ACTIVE,  ///< The enemy is actively pursuing a target.
        DEAD     ///< The enemy is dead and no longer active.
    };

    /**
     * @class Enemy
     * @brief This class represents a generic enemy in the game.
     */
    class Enemy {
    protected:
        double m_enemy_x; ///< The x-coordinate of the enemy.
        double m_enemy_y; ///< The y-coordinate of the enemy.
        double m_velocity; ///< The movement speed of the enemy.
        int m_health; ///< The health of the enemy.
        int m_death_counter; ///< Counter for tracking death.
        double m_attack_range; ///< The range within which the enemy can attack.
        int m_attack_damage; ///< The damage dealt by the enemy's attack.
        Sprite m_enemy_sprite; ///< The sprite representing the enemy.
        Sprite m_dead_enemy_sprite; ///< The sprite representing the dead enemy.
        EnemyBehavior m_behavior; ///< The current behavior state of the enemy.
        double m_target_x; ///< The x-coordinate of the current target.
        double m_target_y; ///< The y-coordinate of the current target.

    public:
        /**
         * @brief Constructor for the Enemy class.
         * @param[in] x - The initial x-coordinate of the enemy.
         * @param[in] y - The initial y-coordinate of the enemy.
         * @param[in] health - The initial health of the enemy.
         * @param[in] velocity - The movement speed of the enemy.
         * @param[in] attack_range - The range within which the enemy can attack.
         * @param[in] attack_damage - The damage dealt by the enemy's attack.
         * @param[in] enemy_behavior - The initial behavior state of the enemy.
         */
        Enemy(double x, double y, int health, double velocity, double attack_range, int attack_damage, EnemyBehavior enemy_behavior);

        /**
         * @brief Virtual destructor for the Enemy class.
         */
        virtual ~Enemy();

        /**
         * @brief Pure virtual method to perform an attack.
         * @param[in,out] target_health - A pointer to the target's health points to be modified.
         */
        virtual void attack(uint* target_health) = 0;

        /**
         * @brief Get the x-coordinate of the enemy.
         * @return The x-coordinate of the enemy.
         */
        double getX() const;

        /**
         * @brief Get the y-coordinate of the enemy.
         * @return The y-coordinate of the enemy.
         */
        double getY() const;

        /**
         * @brief Get the current health of the enemy.
         * @return The current health points of the enemy.
         */
        int getHealth() const;

        /**
         * @brief Set the position of the enemy.
         * @param[in] x - The new x-coordinate of the enemy.
         * @param[in] y - The new y-coordinate of the enemy.
         */
        void setPosition(double x, double y);

        /**
         * @brief Apply damage to the enemy.
         * @param[in] damage - The amount of damage to apply.
         */
        void takeDamage(int damage);

        /**
         * @brief Get the movement speed of the enemy.
         * @return The movement speed of the enemy.
         */
        double getVelocity();

        /**
         * @brief Set the movement speed of the enemy.
         * @param[in] velocity - The new movement speed of the enemy.
         */
        void setVelocity(int velocity);

        /**
         * @brief Handle the death of the enemy.
         */
        void die();

        /**
         * @brief Check if the enemy is dead.
         * @return True if the enemy is dead, false otherwise.
         */
        bool isDead() const;

        /**
         * @brief Get the death counter of the enemy.
         * @return The current value of the death counter.
         */
        int getDeathCounter() const;

        /**
         * @brief Increment the death counter.
         */
        void addCounter();

        /**
         * @brief Get the sprite representing the enemy.
         * @return A reference to the enemy's sprite.
         */
        Sprite& getEnemySprite();

        /**
         * @brief Set the sprite representing the enemy.
         * @param[in] enemy_sprite - The new sprite for the enemy.
         */
        void SetEnemySprite(Sprite enemy_sprite);


        /**
         * @brief Get the sprite representing the dead enemy.
         * @return A reference to the dead enemy's sprite.
         */
        Sprite& getDeadEnemySprite();

        /**
         * @brief Set the sprite representing the dead enemy.
         * @param[in] dead_enemy_sprite - The new sprite for the dead enemy.
         */
        void SetDeadEnemySprite(Sprite dead_enemy_sprite);

        /**
         * @brief Update the enemy's state and behavior.
         * @param[in,out] target_health - A pointer to the target's health points to be modified.
         * @param[in] target_x - The x-coordinate of the target.
         * @param[in] target_y - The y-coordinate of the target.
         * @param[in] obstacles - A 2D vector representing the obstacles in the environment.
         */
        void update(uint* target_health, double target_x, double target_y, std::vector<std::vector<int>> obstacles);

        /**
         * @brief Perform a DDA raycast to check for obstacles between the enemy and the target.
         * @param[in] target_x - The x-coordinate of the target.
         * @param[in] target_y - The y-coordinate of the target.
         * @param[in] obstacles - A 2D vector representing the obstacles in the environment.
         * @return The distance to the nearest obstacle.
         */
        double raycastObstacles(double target_x, double target_y, std::vector<std::vector<int>> obstacles);

        /**
         * @brief Get the type of the enemy.
         * @return A string representing the type of the enemy.
         */
        virtual std::string getEnemyType() const = 0;
    };

    /**
     * @class Zombie
     * @brief This class represents a zombie enemy.
     */
    class Zombie : public Enemy {
    public:
        /**
         * @brief Constructor for the Zombie class.
         * @param[in] x - The initial x-coordinate of the zombie.
         * @param[in] y - The initial y-coordinate of the zombie.
         * @param[in] health - The initial health of the zombie.
         * @param[in] enemy_behavior - The initial behavior state of the zombie.
         */
        Zombie(double x, double y, int health, EnemyBehavior enemy_behavior);

        /**
         * @brief Perform an attack on the target.
         * @param[in,out] target_health - A pointer to the target's health points to be modified.
         */
        void attack(uint* target_health) override;

        /**
         * @brief Get the type of the enemy.
         * @return "Zombie".
         */
        std::string getEnemyType() const override;
    };

    /**
     * @class Alien
     * @brief This class represents an alien enemy.
     */
    class Alien : public Enemy {
    public:
        /**
         * @brief Constructor for the Alien class.
         * @param[in] x - The initial x-coordinate of the alien.
         * @param[in] y - The initial y-coordinate of the alien.
         * @param[in] health - The initial health of the alien.
         * @param[in] enemy_behavior - The initial behavior state of the alien.
         */
        Alien(double x, double y, int health, EnemyBehavior enemy_behavior);

        /**
         * @brief Perform an attack on the target.
         * @param[in,out] target_health - A pointer to the target's health points to be modified.
         */
        void attack(uint* target_health) override;

        /**
         * @brief Get the type of the enemy.
         * @return "Alien".
         */
        std::string getEnemyType() const override;
    };

} // namespace engine

#endif // ENEMY_H
