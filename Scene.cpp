#include "Scene.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) // Macros.

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

	void Scene::addObstacle(int x, int y) {
		m_obstacles.push_back({ x, y }); // Добавляем новое препятствие с координатами (x, y)
	}

	void Scene::removeObstacle(int index) {
		if (index >= 0 && index < m_obstacles.size()) {
			m_obstacles.erase(m_obstacles.begin() + index); // Удаляем препятствие по индексу
		}
	}

	int Scene::getObstacle(int x, int y)
	{
		return m_obstacles[y][x];
	}

	std::vector<std::vector<int>> Scene::getObstacles() const {
		return m_obstacles; // Возвращаем все препятствия
	}

    int Scene::getObstacleSizeY()
    {
        return m_obstacle_size_y;
    }

    int Scene::getObstacleSizeX()
    {
        return m_obstacle_size_x;
    }

	void Scene::readMap(std::string path)
	{
        std::ifstream file(path);
        if (!file.is_open()) {
            std::string str = "Failed to open file " + path;
            THROW_ENGINE_EXCEPTION(str);
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line == "/// Player") {
                double x, y, angle;
                uint health;

                std::getline(file, line); // // X
                file >> x;
                file.ignore(); // Игнорируем оставшийся символ новой строки

                std::getline(file, line); // // Y
                file >> y;
                file.ignore();

                std::getline(file, line); // // Angle
                file >> angle;
                file.ignore();

                std::getline(file, line); // // Health
                file >> health;
                file.ignore();

                m_player = Player(y, x, angle, health);
            }
            else if (line == "/// Camera") {
                double x, y, angle, fov_c;
                int render_distance;

                std::getline(file, line); // // X
                file >> x;
                file.ignore();

                std::getline(file, line); // // Y
                file >> y;
                file.ignore();

                std::getline(file, line); // // Angle
                file >> angle;
                file.ignore();

                std::getline(file, line); // // Fov_c
                file >> fov_c;
                file.ignore();

                std::getline(file, line); // // Render distance
                file >> render_distance;
                file.ignore();

                m_camera = Camera(y, x, angle, fov_c, render_distance);
            }
            else if (line == "/// Obstacle") {
                std::getline(file, line); // // X
                int x, y;
                file >> x;
                file.ignore();

                std::getline(file, line); // // Y
                file >> y;
                file.ignore();

                m_obstacle_size_x = x;
                m_obstacle_size_y = y;

                std::getline(file, line); // // Obstacle
                std::string obstacleLine;
                while (std::getline(file, obstacleLine) && !obstacleLine.empty()) {
                    std::stringstream ss(obstacleLine);
                    std::string value;
                    std::vector<int> row;

                    while (std::getline(ss, value, ',')) {
                        row.push_back(std::stoi(value));
                    }

                    m_obstacles.push_back(row);
                }
            }
        }

        file.close();
	}

    void Scene::processPlayerCollision()
    {
        int check = getObstacle(m_player.getPlayerX(), m_player.getPlayerY());

        if (check) {
            m_player.returnBack();
        }
    }
}
