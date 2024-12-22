#include "Renderer.h"

namespace engine
{
	Renderer::Renderer(Window* window)
	{
		m_renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED);
        m_width = window->getWidth();
        m_height = window->getHeight();
	}

	Renderer::~Renderer()
	{
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
        std::vector<SDL_Color> gradient = {
            {255, 0, 0, 255},   // Красный
            {255, 128, 0, 255}, // Оранжевый
            {255, 255, 0, 255}, // Желтый
            {128, 255, 0, 255}, // Светло-зеленый
            {0, 255, 0, 255},   // Зеленый
            {0, 255, 128, 255}, // Светло-бирюзовый
            {0, 255, 255, 255}, // Циан
            {0, 128, 255, 255}, // Светло-синий
            {0, 0, 255, 255},   // Синий
            {128, 0, 255, 255}, // Фиолетовый
            {255, 0, 255, 255}, // Магента
            {255, 0, 128, 255}  // Розовый
        };


        int gridSizeX = 10;
        int gridSizeY = 10;

        std::vector<std::vector<int>> map = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
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

                double dot_x = cam_x + dx * cur_distance;
                double dot_y = cam_y + dy * cur_distance;

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
                    //            screen.ffDrawDot(i, j, '#'); //lava
                    //        }
                    //    }
                    //}

                }
            }

            prev_distance = cur_distance;
            if (hit == 1 || hit_door == 1) {
                // Определяем цвет стены
                SDL_Color wallColor;
                if (is_corner == 1) {
                    wallColor = { 255, 0, 0, 255 };
                }
                else {
                    int grad_size = sizeof(gradient);
                    if (int(cur_distance) >= grad_size) {
                        wallColor = { 0, 255, 0, 255 };
                    }
                    else {
                        int color_index = int((grad_size - cur_distance));
                        wallColor = { 0, 255, 0, 255 };
                    }
                }

                if (hit_door == 1) {
                    cur_distance += 0.7;
                    wallColor = { 0, 255, 0, 255 }; // Зеленый цвет для двери
                }

                double n_c = cur_distance * cos(ray_angle - cam_angle); // fish eye fix

                int ceiling = (double)(scr_h / 2) - (scr_h / n_c);
                int floorr = scr_h - ceiling;

                // Рисуем потолок
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255); // Синий цвет для потолка
                SDL_RenderDrawLine(m_renderer, column, 0, column, ceiling);

                // Рисуем стену
                SDL_SetRenderDrawColor(m_renderer, wallColor.r, wallColor.g, wallColor.b, wallColor.a);
                SDL_RenderDrawLine(m_renderer, column, ceiling, column, floorr);

                // Рисуем пол
                SDL_SetRenderDrawColor(m_renderer, 128, 128, 128, 255); // Серый цвет для пола
                SDL_RenderDrawLine(m_renderer, column, floorr, column, scr_h);
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

}
