#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>

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
        double m_player_angle; ///< Player rotation angle
    public:
        Player(); ///< Default constructor
        Player(double player_y, double player_x, double player_angle, uint player_health); ///< Constructor
        ~Player(); ///< Destructor
        
        void setPlayerCoords(double player_y, double player_x);
        void setPlayerY(double player_y);
        double getPlayerY();
        void setPlayerX(double player_x);
        double getPlayerX();
        void setPlayerPrevY();
        void setPlayerPrevX();
        void setPlayerAngle(double player_angle);
        double getPlayerAngle();
        void setPlayerHealth(uint player_health);
        uint getPlayerHealth();

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
        void incrementPlayerAngle(double value);

        /**
         * @brief Adds value to rotation angle.
         * @param[in] value -Subtracted value.
         */
        void decrementPlayerAngle(double value);

        /**
         * @brief Return player to previous position.
         */
        void returnBack();

        /**
         * @brief Applies damage to the player.
         * @param[in] value -Subtracted value.
         */
        void applyDamage(int damage);
    };

}

#endif // PLAYER_H
