#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <corecrt_math_defines.h>

typedef unsigned int uint;

/**
 * @namespace engine
 * @brief This namespace contains classes for game engine.
 */
namespace engine 
{
    /**
     * @brief Player class
     */
	class Player
	{
    private:
        uint m_player_health; ///< Player health
        double m_player_prev_y; ///< Player previous y (for collision)
        double m_player_prev_x; ///< Player previous x (for collision)
        double m_player_y; ///< Player y 
        double m_player_x; ///< Player x 
        double m_player_angle; ///< Player rotation angle (radians)
    public:
        /**
         * @brief Default constructor.
         * PLAYER_HEALTH = 100
         * PLAYER_Y = 0
         * PLAYER_X = 0
         * PLAYER_ANGLE = 0
         * PLAYER_PREV_Y = 0
         * PLAYER_PREV_X = 0
         */
        Player(); ///< Default constructor

        /**
         * @brief Player constructor.
         * @param[in] player_y -Player y. 
         * @param[in] player_x -Player x.
         * @param[in] player_angle -Player rotation angle (radians).
         * @param[in] player_health -Player health.
         */
        Player(double player_y, double player_x, double player_angle, uint player_health); ///< Constructor

        ~Player(); ///< Destructor
        
        /**
         * @brief Set player cords.
         * @param[in] player_y -Player y.
         * @param[in] player_x -Player x.
         */
        void setPlayerCoords(double player_y, double player_x);

        /**
         * @brief Set player y cord.
         * @param[in] player_y -Player y.
         */
        void setPlayerY(double player_y);
        double getPlayerY(); ///< Get player y cord.

        /**
         * @brief Set player x cord.
         * @param[in] player_x -Player x.
         */
        void setPlayerX(double player_x);
        double getPlayerX(); ///< Get player x cord.

        void setPlayerPrevY();///< Set player y cord to previous y cord.
        void setPlayerPrevX(); ///< Set player x cord to previous x cord.

        /**
         * @brief Set player rotation angle.
         * @param[in] player_angle -Player angle.
         */
        void setPlayerAngle(double player_angle);
        double getPlayerAngle(); ///< Get player angle (radians).

        /**
         * @brief Set player health.
         * @param[in] player_health -Player health.
         */
        void setPlayerHealth(uint player_health);
        uint getPlayerHealth(); ///< Get player health.

        /**
         * @brief Moves player forward or backward.
         * @param[in] step -Movement step.
         */
        void movePlayer(double step);

        /**
         * @brief Moves player right or left.
         * @param[in] step -Movement step.
         */
        void movePlayerSide(double step);

        /**
         * @brief Moves player diagonally.
         * @param[in] step_foward -Foward movement step.
         * @param[in] step_foward -Side movement step.
         */
        void movePlayerDiagonal(double step_forward, double step_side);

        /**
         * @brief Adds value to rotation angle.
         * @param[in] value -Added value.
         */
        void addPlayerAngle(double value);

        /**
         * @brief Return player to previous position.
         */
        void returnBack();

        /**
         * @brief Applies damage to the player.
         * @param[in] value -Subtracted value.
         */
        void applyDamage(int damage);

        uint* getHealthPointer();
    };

}

#endif // PLAYER_H
