#ifndef SCENE_H
#define SCENE_H

#include "Player.h"
#include "Camera.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "EngineException.h"
#include <iostream>
#include <unordered_map>
#include "Enemy.h"
#include <functional>
#include <string>
#include <utility>
#include <algorithm>
#include <cmath> 
#include <queue>
#include <unordered_set>
#include "Sprite.h"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ (hash2 << 1);
    }
};

typedef unsigned int uint;

/**
 * @namespace engine
 * @brief This namespace contains classes for game engine.
 */
namespace engine
{
    /**
     * @class Scene
     * @brief Represents a scene in the game, containing players, cameras, obstacles, and decorations.
     */
    class Scene
    {
    private:
        Player m_player; ///< Scene player
        Camera m_camera; ///< Scene camera
        std::vector<std::vector<int>> m_obstacles; ///< 2D array of obstacles
        std::unordered_map<std::pair<int, std::string>, std::string, pair_hash> textures_predefine; ///< Predefined textures
        uint m_obstacle_size_x; ///< Width of the obstacle grid
        uint m_obstacle_size_y; ///< Height of the obstacle grid
        std::vector<Enemy*> m_enemies; ///< List of enemies in the scene
        std::vector<Sprite> m_decorations; ///< Decorative sprites
        void updateEnemiesAnimation(); ///< Updates enemy animations
        void updateDecorationsAnimations(); ///< Updates decoration animations

    public:
        /**
         * @brief Default constructor for the Scene class.
         */
        Scene();

        /**
         * @brief Destructor for the Scene class.
         */
        ~Scene();

        /**
         * @brief Gets a reference to the player in the scene.
         * @return Reference to the Player object.
         */
        Player& getPlayer();

        /**
         * @brief Gets a copy of the player in the scene.
         * @return A copy of the Player object.
         */
        Player getPlayer() const;

        /**
         * @brief Adds a player to the scene.
         * @param[in] y - The y coordinate of the player's position.
         * @param[in] x - The x coordinate of the player's position.
         * @param[in] angle - The angle of the player.
         * @param[in] health - The health of the player.
         */
        void addPlayer(uint y, uint x, int angle, uint health);

        /**
         * @brief Gets a reference to the camera in the scene.
         * @return Reference to the Camera object.
         */
        Camera& getCamera();

        /**
         * @brief Gets a copy of the camera in the scene.
         * @return A copy of the Camera object.
         */
        Camera getCamera() const;

        /**
         * @brief Adds a camera to the scene.
         * @param[in] camera_y - The y coordinate of the camera's position.
         * @param[in] camera_x - The x coordinate of the camera's position.
         * @param[in] camera_angle - The angle of the camera in radians.
         * @param[in] fov_c - The field of view of the camera in degrees.
         * @param[in] render_distance - The render distance of the camera.
         */
        void addCamera(int camera_y, int camera_x, double camera_angle, double fov_c, int render_distance);

        /**
         * @brief Adds an obstacle to the scene.
         * @param[in] x - The x coordinate of the obstacle.
         * @param[in] y - The y coordinate of the obstacle.
         */
        void addObstacle(int x, int y);

        /**
         * @brief Removes an obstacle from the scene.
         * @param[in] index - The index of the obstacle to remove.
         */
        void removeObstacle(int index);

        /**
         * @brief Gets the obstacle at the specified coordinates.
         * @param[in] x - The x coordinate of the obstacle.
         * @param[in] y - The y coordinate of the obstacle.
         * @return The ID of the obstacle at the specified coordinates.
         */
        int getObstacle(int x, int y);

        /**
         * @brief Gets all obstacles in the scene.
         * @return A 2D vector of obstacles.
         */
        std::vector<std::vector<int>>
            getObstacles() const;

        /**
         * @brief Gets the height of the obstacle grid.
         * @return The height of the obstacle grid.
         */
        int getObstacleSizeY();

        /**
         * @brief Gets the width of the obstacle grid.
         * @return The width of the obstacle grid.
         */
        int getObstacleSizeX();

        /**
         * @brief Gets the decorative sprites in the scene.
         * @return A vector of decorative Sprite objects.
         */
        std::vector<Sprite> getDecorations();

        /**
         * @brief Loads a map from the specified file path.
         * @param[in] path - The file path to load the map from.
         */
        void loadMap(std::string path);

        /**
         * @brief Saves the current map to the specified file path.
         * @param[in] path - The file path to save the map to.
         */
        void saveMap(std::string path);

        /**
         * @brief Processes player collision with obstacles and enemies.
         */
        void processPlayerCollision();

        /**
         * @brief Gets predefined textures.
         * @return A map of predefined textures.
         */
        std::unordered_map<std::pair<int, std::string>, std::string, pair_hash> getTexturesPredefine() const;

        /**
         * @brief Adds an enemy to the scene.
         * @param[in] enemy - Pointer to the Enemy object to add.
         */
        void addEnemy(Enemy* enemy);

        /**
         * @brief Updates the state of all enemies in the scene.
         */
        void updateEnemies();

        /**
         * @brief Gets the count of enemies in the scene.
         * @return The number of enemies.
         */
        int getEnemyCount();

        /**
         * @brief Calculates the distance from the specified enemy to the player.
         * @param[in] enemy - Pointer to the Enemy object.
         * @return The distance to the player.
         */
        double calculateDistanceToPlayer(const Enemy* enemy);

        /**
         * @brief Calculates the distance from the specified sprite to the player.
         * @param[in] sprite - Pointer to the Sprite object.
         * @return The distance to the player.
         */
        double calculateDistanceToSprite(const Sprite* sprite);

        /**
         * @brief Sorts the enemies in the scene by their distance to the player.
         */
        void sortEnemiesByDistance();

        /**
         * @brief Gets all enemies in the scene.
         * @return A vector of pointers to Enemy objects.
         */
        std::vector<Enemy*> getEnemies();

        /**
         * @brief Fires a projectile or attack from the player.
         */
        void fire();

        /**
         * @brief Performs a DDA raycast from the player to detect obstacles.
         * @param[in] cast_distance - The distance to cast the ray.
         * @return The distance to the first obstacle encountered.
         */
        double raycastObstacleFromPlayer(int cast_distance);

        /**
         * @brief Updates animations for all entities in the scene.
         */
        void updateAnimations();
    };

} // namespace engine

#endif // SCENE_H
