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
		uint m_obstacle_size_x;
		uint m_obstacle_size_y;
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

		void readMap(std::string path);

		void processPlayerCollision();
	};

} // engine

#endif // SCENE_H






