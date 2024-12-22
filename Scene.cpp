#include "Scene.h"

namespace engine
{
	engine::Scene::Scene()
	{
	}

	engine::Scene::~Scene()
	{
	}

	Player& engine::Scene::getPlayer()
	{
		return m_player;
	}

	Player engine::Scene::getPlayer() const
	{
		return m_player;
	}

	void Scene::addPlayer(uint y, uint x, int angle, uint health)
	{
		m_player = Player(y, x, angle, health);
	}

	Camera& Scene::getCamera()
	{
		return m_camera;
	}

	Camera Scene::getCamera() const
	{
		return m_camera;
	}

	void Scene::addCamera(int camera_y, int camera_x, double camera_angle, double fov_c, int render_distance)
	{
		m_camera = Camera(camera_y, camera_x, camera_angle, fov_c, render_distance);
	}
}
