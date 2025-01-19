#include "Scene.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) // Macros.

namespace engine
{
	engine::Scene::Scene()
	{
	}

	engine::Scene::~Scene()
	{
        for (Enemy* enemy : m_enemies) {
            delete enemy;
        }
        m_enemies.clear();
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
        if (x < 0 || x >= m_obstacle_size_x || y < 0 || y >= m_obstacle_size_y) {
            return 0;
        }
		else return m_obstacles[y][x];
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
            else if (line == "/// Textures") {
                while (true) {
                    int key;
                    std::string name, texture;

                    if (!(file >> key)) break;
                    file.ignore();

                    std::getline(file, name);
                    if (name.empty()) break;

                    std::getline(file, texture);
                    if (texture.empty()) break;

                    textures_predefine[std::make_pair(key, name)] = texture;
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
    std::unordered_map<std::pair<int, std::string>, std::string, pair_hash> Scene::getTexturesPredefine()
    {
        return textures_predefine;
    }

    void Scene::addEnemy(double x, double y, int health)
    {
        Enemy* enemy = new Zombie(x, y, health);
        m_enemies.push_back(enemy);
    }

    void Scene::updateEnemies() {
        for (size_t i = 0; i < m_enemies.size(); ) {
            m_enemies[i]->update();

            if (m_enemies[i]->getHealth() <= 0) {
                delete m_enemies[i];
                m_enemies.erase(m_enemies.begin() + i);
            }
            else {
                ++i;
            }
        }
    }

    void Scene::sortEnemiesByDistance() {
        std::sort(m_enemies.begin(), m_enemies.end(), [this](const Enemy* a, const Enemy* b) {
            return calculateDistance(a) > calculateDistance(b);
        });
    }

    double Scene::calculateDistance(const Enemy* enemy) {
        double dx = enemy->getX() - m_player.getPlayerX();
        double dy = enemy->getY() - m_player.getPlayerY();
        return std::sqrt(dx * dx + dy * dy);
    }

    std::vector<Enemy*> Scene::getEnemies()
    {
        return m_enemies;
    }


}
