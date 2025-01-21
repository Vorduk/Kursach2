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
	 * @brief Scene class.
	 */
	class Scene
	{
	private:
		Player m_player; ///< Scene palyer
		Camera m_camera; ///< Scene camera
		std::vector<std::vector<int>> m_obstacles; ///< 2D array of obstacles
		std::unordered_map<std::pair<int, std::string>, std::string, pair_hash> textures_predefine;
		uint m_obstacle_size_x;
		uint m_obstacle_size_y;
		std::vector<Enemy*> m_enemies;
	public:
		Scene(); ///< Contructor
		~Scene(); ///< Destructor

		Player& getPlayer();
		Player getPlayer() const;
		void addPlayer(uint y, uint x, int angle, uint health);

		Camera& getCamera();
		Camera getCamera() const;
		void addCamera(int camera_y, int camera_x, double camera_angle, double fov_c, int render_distance);

		void addObstacle(int x, int y); 
		void removeObstacle(int index); 
		int getObstacle(int x, int y);
		std::vector<std::vector<int>> getObstacles() const;

		int getObstacleSizeY();
		int getObstacleSizeX();

		void loadMap(std::string path);

		void processPlayerCollision();

		std::unordered_map<std::pair<int, std::string>, std::string, pair_hash> getTexturesPredefine() const;

		void addEnemy(Enemy* enemy);
		void updateEnemies();

		double calculateDistanceToPlayer(const Enemy* enemy);
		void sortEnemiesByDistance();
		std::vector<Enemy*> getEnemies();

		void fire();

		double raycastObstacleFromPlayer(int cast_distatnce);
	};

} // engine

#endif // SCENE_H






