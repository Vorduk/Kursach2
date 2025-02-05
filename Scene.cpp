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
		m_obstacles.push_back({ x, y });
	}

	void Scene::removeObstacle(int index) {
		if (index >= 0 && index < m_obstacles.size()) {
			m_obstacles.erase(m_obstacles.begin() + index);
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
		return m_obstacles;
	}

    int Scene::getObstacleSizeY()
    {
        return m_obstacle_size_y;
    }

    int Scene::getObstacleSizeX()
    {
        return m_obstacle_size_x;
    }

    std::vector<Sprite> Scene::getDecorations()
    {
        return m_decorations;
    }

	void Scene::loadMap(std::string path)
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

                std::getline(file, line); ///< // X
                file >> x;
                file.ignore(); 

                std::getline(file, line); ///< // Y
                file >> y;
                file.ignore();

                std::getline(file, line); ///< // Angle
                file >> angle;
                file.ignore();

                std::getline(file, line); ///< // Health
                file >> health;
                file.ignore();

                m_player = Player(y, x, angle, health);
            }
            else if (line == "/// Camera") {
                double x, y, angle, fov_c;
                int render_distance;

                std::getline(file, line); ///< // X
                file >> x;
                file.ignore();

                std::getline(file, line); ///< // Y
                file >> y;
                file.ignore();

                std::getline(file, line); ///< // Angle
                file >> angle;
                file.ignore();

                std::getline(file, line); ///< // Fov_c
                file >> fov_c;
                file.ignore();

                std::getline(file, line); ///< // Render distance
                file >> render_distance;
                file.ignore();

                m_camera = Camera(y, x, angle, fov_c, render_distance);
            }
            else if (line == "/// Enemies") {
                while (true) {
                    
                    std::getline(file, line); ///< // Type
                    if (line.empty()) break;

                    std::string enemy_type;
                    std::getline(file, enemy_type);
                    if (enemy_type.empty()) break; ///< If line is empty

                    double x, y;
                    int health;
                    std::string texture_id;
                    int frames;
                    std::string dead_texture_id;
                    int frames_dead;

                    std::getline(file, line); ///< // X
                    file >> x;
                    file.ignore();

                    std::getline(file, line); ///< // Y
                    file >> y;
                    file.ignore();

                    std::getline(file, line); ///< // Health
                    file >> health;
                    file.ignore();

                    std::getline(file, line); ///< // Textures id
                    std::getline(file, texture_id);
                    file >> frames;
                    file.ignore();
                    std::getline(file, dead_texture_id);
                    file >> frames_dead;
                    file.ignore();

                    Enemy* enemy = nullptr;
                    if (enemy_type == "Zombie") {
                        enemy = new Zombie(x, y, health, IDLE);
                    }
                    else if (enemy_type == "Alien") {
                        enemy = new Alien(x, y, health, IDLE);
                    }

                    if (enemy) { ///< Texture set
                        enemy->SetEnemySprite(Sprite(x, y, frames, 0, texture_id));
                        enemy->SetDeadEnemySprite(Sprite(x, y, frames_dead, 0, dead_texture_id));
                        addEnemy(enemy); 
                    }
                }
            }
            else if (line == "/// Decorations") {
                while (true) {
                    std::getline(file, line); ///< // Sprite
                    if (line.empty()) break;

                    double x, y;
                    std::string texture_id;
                    int frames;

                    std::getline(file, line); ///< // X
                    file >> x;
                    file.ignore();

                    std::getline(file, line); ///< // Y
                    file >> y;
                    file.ignore();

                    std::getline(file, line); ///< // Textures id
                    std::getline(file, texture_id);
                    file >> frames;
                    file.ignore();

                    Sprite new_sprite = Sprite(x, y, frames, 0, texture_id);
                    m_decorations.push_back(new_sprite);
                }
            }
            else if (line == "/// Obstacle") {
                std::getline(file, line); ///< // X
                int x, y;
                file >> x;
                file.ignore();

                std::getline(file, line); ///< // Y
                file >> y;
                file.ignore();

                m_obstacle_size_x = x;
                m_obstacle_size_y = y;

                std::getline(file, line); ///< // Obstacle
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

                    if (!(file >> key)) break; ///< integer id
                    file.ignore();

                    std::getline(file, name); ///< string id
                    if (name.empty()) break;

                    std::getline(file, texture); ///< image file name or path
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

    std::unordered_map<std::pair<int, std::string>, std::string, pair_hash> Scene::getTexturesPredefine() const
    {
        return textures_predefine;
    }

    void Scene::addEnemy(Enemy* enemy)
    {
        m_enemies.push_back(enemy);
    }

    void Scene::updateEnemies() {
        sortEnemiesByDistance();

        for (size_t i = 0; i < m_enemies.size(); ) {
            Enemy* enemy = m_enemies[i];
            
            enemy->update(m_player.getHealthPointer(), m_player.getPlayerX(), m_player.getPlayerY(), m_obstacles);

            if (enemy->getDeathCounter() > 20) {
                delete enemy;
                m_enemies.erase(m_enemies.begin() + i);
                continue;
            }
            else {
                ++i;
            }  
        }
    }

    void Scene::sortEnemiesByDistance() {
        std::sort(m_enemies.begin(), m_enemies.end(), [this](const Enemy* a, const Enemy* b) {
            return calculateDistanceToPlayer(a) > calculateDistanceToPlayer(b);
        });
    }

    void Scene::saveMap(std::string path)
    {
        std::ofstream file(path);
        if (!file.is_open()) {
            std::string str = "Failed to open file " + path;
            THROW_ENGINE_EXCEPTION(str);
            return;
        }

        file << "/// Player\n";
        file << "// X\n" << m_player.getPlayerX() << "\n";
        file << "// Y\n" << m_player.getPlayerY() << "\n"; 
        file << "// Angle\n" << m_player.getPlayerAngle() << "\n"; 
        file << "// Health\n" << m_player.getPlayerHealth() << "\n"; 
        file << "\n";

        file << "/// Camera\n";
        file << "// X\n" << m_camera.getCameraX() << "\n";
        file << "// Y\n" << m_camera.getCameraY() << "\n"; 
        file << "// Angle\n" << m_camera.getCameraAngle() << "\n";
        file << "// Fov_c\n" << m_camera.getFovC() << "\n";
        file << "// Render distance\n" << m_camera.getRenderDistance() << "\n";
        file << "\n";

        file << "/// Enemies\n";
        for (const auto& enemy : m_enemies) { 
            file << "// Type\n" << enemy->getEnemyType() << "\n";
            file << "// X\n" << enemy->getX() << "\n"; 
            file << "// Y\n" << enemy->getY() << "\n"; 
            file << "// Health\n" << enemy->getHealth() << "\n"; 
            file << "// Textures id\n" << enemy->getEnemySprite().m_texture_id << "\n"; 
            file << enemy->getEnemySprite().m_frames << "\n"; 
            file << enemy->getDeadEnemySprite().m_texture_id << "\n"; 
            file << enemy->getDeadEnemySprite().m_frames << "\n";
        }
        file << "\n";

        file << "/// Decorations\n";
        for (const auto& decoration : m_decorations) { 
            file << "// Sprite\n";
            file << "// X\n" << decoration.m_x << "\n"; 
            file << "// Y\n" << decoration.m_y << "\n";
            file << "// Texture id & frames count\n";
            file << decoration.m_texture_id << "\n";
            file << decoration.m_frames << "\n";
        }
        file << "\n";

        file << "/// Obstacle\n";
        file << "// X\n" << m_obstacle_size_x << "\n";
        file << "// Y\n" << m_obstacle_size_y << "\n";
        file << "// Obstacle\n";
        for (const auto& row : m_obstacles) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) {
                    file << ", ";
                }
            }
            file << "\n";
        }
        file << "\n";

        file << "/// Textures\n";
        for (const auto& texture : textures_predefine) { 
            file << texture.first.first << "\n"; 
            file << texture.first.second << "\n"; 
            file << texture.second << "\n";
        }

        file.close(); 
    }

    double Scene::calculateDistanceToPlayer(const Enemy* enemy) {
        double dx = enemy->getX() - m_player.getPlayerX();
        double dy = enemy->getY() - m_player.getPlayerY();
        return std::sqrt(dx * dx + dy * dy);
    }

    double Scene::calculateDistanceToSprite(const Sprite* sprite)
    {
        double dx = sprite->m_x - m_player.getPlayerX();
        double dy = sprite->m_y - m_player.getPlayerY();
        return std::sqrt(dx * dx + dy * dy);
    }

    std::vector<Enemy*> Scene::getEnemies()
    {
        return m_enemies;
    }

    void Scene::fire()
    {
        for (size_t i = 0; i < m_enemies.size(); ++i) {
            int enemy_distance = calculateDistanceToPlayer(m_enemies[i]);

            double player_x = m_player.getPlayerX();
            double player_y = m_player.getPlayerY();
            double player_angle = m_player.getPlayerAngle();

            float sprite_dir = atan2(m_enemies[i]->getY() - player_y, m_enemies[i]->getX() - player_x);
            while (sprite_dir - player_angle > M_PI) sprite_dir -= 2 * M_PI;
            while (sprite_dir - player_angle < -M_PI) sprite_dir += 2 * M_PI;

            float sprite_angle = sprite_dir - player_angle;

            double cast = raycastObstacleFromPlayer(25);
            bool cast_check = cast == -1.0 ? true : (enemy_distance - cast < 0.1);

            int area = 25;

            if (abs(sprite_angle) < (M_PI/6/enemy_distance) && enemy_distance < area && cast_check)
            {
                m_enemies[i]->takeDamage(15);
            }
        }
    }

    double Scene::raycastObstacleFromPlayer(int cast_distatnce) {

        double player_x = m_player.getPlayerX();
        double player_y = m_player.getPlayerY();

        int map_check_x = player_x;
        int map_check_y = player_y;

        int hit = 0;
        int hit_door = 0;

        double ray_angle = m_player.getPlayerAngle();

        float dx = cos(ray_angle);
        float dy = sin(ray_angle);

        double unit_step_size_x = sqrt(1 + (dy / dx) * (dy / dx));
        double unit_step_size_y = sqrt(1 + (dx / dy) * (dx / dy));

        double ray_length_x;
        double ray_length_y;

        double step_x;
        double step_y;

        if (dx < 0)
        {
            step_x = -1;
            ray_length_x = (player_x - float(map_check_x)) * unit_step_size_x;
        }
        else {
            step_x = 1;
            ray_length_x = (float(map_check_x + 1) - player_x) * unit_step_size_x;
        }

        if (dy < 0)
        {
            step_y = -1;
            ray_length_y = (player_y - float(map_check_y)) * unit_step_size_y;
        }
        else {
            step_y = 1;
            ray_length_y = (float(map_check_y + 1) - player_y) * unit_step_size_y;
        }

        double dot_x;
        double dot_y;

        double cur_distance = 0.0;
        while (cur_distance < cast_distatnce) {

            // walk
            if (ray_length_x < ray_length_y) {
                map_check_x += step_x;
                cur_distance = ray_length_x;
                ray_length_x += unit_step_size_x;
            }
            else {
                map_check_y += step_y;
                cur_distance = ray_length_y;
                ray_length_y += unit_step_size_y;
            }

            dot_x = player_x + dx * cur_distance;
            dot_y = player_y + dy * cur_distance;

            if (map_check_x >= 0 && map_check_x < m_obstacle_size_x && map_check_y >= 0 && map_check_y < m_obstacle_size_y) {
                hit = getObstacle(map_check_x, map_check_y);
                if (hit != 0) {
                    break;
                }
            }
        }

        if (hit != 0) {
            return cur_distance;
        }
        else return -1.0;
    }

    int Scene::getEnemyCount()
    {
        return m_enemies.size();
    }

    void Scene::updateAnimations()
    {
        updateDecorationsAnimations();
        updateEnemiesAnimation();
    }

    void Scene::updateEnemiesAnimation()
    {
        for (size_t i = 0; i < m_enemies.size(); ++i) {
            Enemy* enemy = m_enemies[i];
            if (enemy->getEnemySprite().m_current_frame < enemy->getEnemySprite().m_frames - 1) {
                enemy->getEnemySprite().m_current_frame += 1;
            }
            else {
                enemy->getEnemySprite().m_current_frame = 0;
            }

        }
    }

    void Scene::updateDecorationsAnimations()
    {
        for (size_t i = 0; i < m_decorations.size(); ++i) {
            Sprite decoration = m_decorations[i];
            if (decoration.m_current_frame < decoration.m_frames - 1) {
                decoration.m_current_frame += 1;
            }
            else {
                decoration.m_current_frame = 0;
            }

        }
    }


}
