#include "Renderer.h"

namespace engine
{
	Renderer::Renderer(Window* window)
	{
		m_renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
        m_width = window->getWidth();
        m_height = window->getHeight();
        m_texture_manager = new TextureManager(m_renderer);
	}

	Renderer::~Renderer()
	{
        delete m_texture_manager;
		SDL_DestroyRenderer(m_renderer);
	}

	void Renderer::clear()
	{
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::present()
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::drawRectangle(int x, int y, int width, int height, SDL_Color color)
	{
		SDL_Rect rect = { x, y, width, height };
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(m_renderer, &rect);
	}

	void Renderer::renderSceneDDA(Camera* camera)
	{
        int gridSizeX = 10;
        int gridSizeY = 10;

        std::vector<std::vector<int>> map = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
            {1, 0, 0, 0, 0, 0, 3, 3, 0, 1,},
            {1, 0, 0, 0, 0, 0, 0, 3, 0, 1,},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1,},
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 1,},
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 1,},
            {1, 0, 0, 0, 0, 0, 1, 1, 0, 1,},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        };

        int rays_n = m_width;
        int scr_h = m_height;

        double cam_angle = camera->getCameraAngle();
        double cam_fov = camera->getFov();
        double cam_x = camera->getCameraX();
        double cam_y = camera->getCameraY();
        double render_distance = camera->getRenderDistance();       

        double prev_distance;

        for (int column = 0; column < rays_n; column++) {
            int is_corner = 0;

            int map_check_x = cam_x;
            int map_check_y = cam_y;

            int hit = 0;
            int hit_door = 0;

            double ray_angle = cam_angle - (cam_fov / 2) + ((column * cam_fov) / rays_n);

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
                ray_length_x = (cam_x - float(map_check_x)) * unit_step_size_x;
            }
            else {
                step_x = 1;
                ray_length_x = (float(map_check_x + 1) - cam_x) * unit_step_size_x;
            }

            if (dy < 0)
            {
                step_y = -1;
                ray_length_y = (cam_y - float(map_check_y)) * unit_step_size_y;
            }
            else {
                step_y = 1;
                ray_length_y = (float(map_check_y + 1) - cam_y) * unit_step_size_y;
            }

            double dot_x;
            double dot_y;

            double cur_distance = 0.0;
            while (cur_distance < render_distance) {

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

                dot_x = cam_x + dx * cur_distance;
                dot_y = cam_y + dy * cur_distance;

                if (map_check_x >= 0 && map_check_x < gridSizeX && map_check_y >= 0 && map_check_y < gridSizeY) {
                    int check = map[map_check_y][map_check_x];
                    if (check == 1) {
                        hit = 1;
                        if ((fabs(dot_x - round(dot_x)) < 0.05) && (fabs(dot_y - round(dot_y)) < 0.05)) {
                            is_corner = 1;
                        }
                        break;
                    }
                    else if (check == 2) {
                        hit_door = 1;
                        break;
                    }
                    //else if (check == 3) {  //lava
                    //    int floor_size = 1; double n_c = cur_distance * cos(ray_angle - cam_angle);
                    //    int ceiling = (double)(scr_h / 2) - (scr_h / n_c);
                    //    int floorr = scr_h - ceiling;
                    //    for (int i = floorr - floor_size; i <= floorr; i++) {
                    //        for (int j = column - floor_size; j <= column + floor_size; j++) {
                    //            SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
                    //            SDL_RenderDrawPoint(m_renderer, i, j); //lava
                    //        }
                    //    }
                    //}

                }
            }

            prev_distance = cur_distance;
            if (hit == 1 || hit_door == 1) {

                //if (hit_door == 1) {
                //    cur_distance += 0.7;
                //    wallColor = { 0, 255, 0, 255 }; // Зеленый цвет для двери
                //}

                double n_c = cur_distance * cos(ray_angle - cam_angle); // fish eye fix

                int ceiling = (double)(scr_h / 2) - (scr_h / n_c);

                // Рисуем потолок
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255); // Синий цвет для потолка
                SDL_RenderDrawLine(m_renderer, column, 0, column, ceiling);

                double test_x = (double)dot_x - (int)dot_x;
                double test_y = (double)dot_y - (int)dot_y;

                // Рисуем стену
                if (test_x > 0.00001)
                {
                    int tex_col = round(((double)dot_x - (int)dot_x) * 1024);
                    renderTexture("putin", column, ceiling, column, scr_h - (2 * ceiling), tex_col, 0, tex_col + 1, 1024);
                }

                if (test_y > 0.00001)
                {
                    int tex_col = round(((double)dot_y - (int)dot_y) * 1024);
                    renderTexture("putin", column, ceiling, column, scr_h - (2 * ceiling), tex_col, 0, tex_col + 1, 1024);
                }

                // Рисуем пол
                SDL_SetRenderDrawColor(m_renderer, 128, 128, 128, 255); // Серый цвет для пола
                SDL_RenderDrawLine(m_renderer, column, scr_h - ceiling, column, scr_h);
            }
            else
            {
                SDL_SetRenderDrawColor(m_renderer, 128, 128, 128, 255); // Серый цвет для пола
                SDL_RenderDrawLine(m_renderer, column, (scr_h / 2), column, scr_h);

                SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
                SDL_RenderDrawLine(m_renderer, column, 0, column, (scr_h / 2));
            }



            //for (const auto& enemy : map.getEnemies()) {
            //    std::string enemy_type = typeid(*enemy).name(); // Nmae
            //    if (enemy_type == typeid(Goblin).name()) {
            //        enemy_type = "Goblin";
            //    }
            //    else if (enemy_type == typeid(Orc).name()) {
            //        enemy_type = "Orc";
            //    }

            //    double ey = enemy->getY();
            //    double ex = enemy->getX();


            //    // todo: enemy render
            //}
        }

        
    }

    bool Renderer::loadTexture(const std::string& id, const std::string& path) {
        return m_texture_manager->loadTexture(id, path);
    }

    void Renderer::renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2) {
        m_texture_manager->renderTexture(texture_id, x, y, render_width, render_height, cut_x1, cut_y1, cut_x2, cut_y2);
    }

    void Renderer::freeTexture(const std::string& id) {
        m_texture_manager->freeTexture(id);
    }

}
