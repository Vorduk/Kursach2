#ifndef SCENE_H
#define SCENE_H

#include "Player.h"
#include "Camera.h"

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
	public:
		Scene(); ///< Contructor
		~Scene(); ///< Destructor

		Player& getPlayer();
		Player getPlayer() const;
		void addPlayer(uint y, uint x, int angle, uint health);

		Camera& getCamera();
		Camera getCamera() const;
		void addCamera(int camera_y, int camera_x, double camera_angle, double fov_c, int render_distance);
	};

} // engine

#endif // SCENE_H






