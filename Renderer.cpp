#include "Renderer.h"

namespace engine
{
    void Renderer::drawWallTextures(int wall_id, int axis, int column, int ceiling, int height, int texture_column)
    {
        // Get the texture ID for the given wall_id
        auto it = wall_texture_map.find(wall_id);
        if (it != wall_texture_map.end()) {
            std::string texture_id = it->second;

            // Call renderTexture based on the axis
            if (axis == 0) { 
                renderTexture(texture_id, column, ceiling, column, height, texture_column, 0, texture_column + 1, 1024, false, false);
            }
            else { 
                renderTexture(texture_id, column, ceiling, column, height, texture_column, 0, texture_column + 1, 1024, false, false);
            }
        }
        else {
            // todo
        }
    }

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
        int gridSizeX = 20;
        int gridSizeY = 20;

        std::vector<std::vector<int>> map = {
            {1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, },
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
            {1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, },
            {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, },
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, },
            {2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, },
            {2, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, },
            {2, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, },
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
            {1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 1, },
            {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, },
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, },
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 2, },
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 2, },
            {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, },
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, },
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
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
                    hit = map[map_check_y][map_check_x];
                    if (hit != 0) {
                        if ((fabs(dot_x - round(dot_x)) < 0.05) && (fabs(dot_y - round(dot_y)) < 0.05)) {
                            is_corner = 1;
                        }
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
            if (hit != 0) {

                double n_c = cur_distance * cos(ray_angle - cam_angle); ///< Distance with fish eye fix

                int ceiling = (double)(scr_h / 2) - (scr_h / n_c); ///< Ceiling height on the screen

                // Drawing ceiling
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255); // Синий цвет для потолка
                SDL_RenderDrawLine(m_renderer, column, 0, column, ceiling);

                // What side of wall?
                double test_x = (double)dot_x - (int)dot_x;
                double test_y = (double)dot_y - (int)dot_y;

                int height = scr_h - (2 * ceiling);

                // Drawing wall
                if (test_x > 0.00001)
                {
                    int tex_col = round(((double)dot_x - (int)dot_x) * 1024);
                    drawWallTextures(hit, 0, column, ceiling, height, tex_col);
                }

                if (test_y > 0.00001)
                {
                    int tex_col = round(((double)dot_y - (int)dot_y) * 1024);
                    drawWallTextures(hit, 1, column, ceiling, height, tex_col);
                }

                // Drawing floor
                SDL_SetRenderDrawColor(m_renderer, 128, 128, 128, 255); // Серый цвет для пола
                SDL_RenderDrawLine(m_renderer, column, scr_h - ceiling, column, scr_h);
            }
            else
            {
                // Drawing floor outside the map
                SDL_SetRenderDrawColor(m_renderer, 128, 128, 128, 255);
                SDL_RenderDrawLine(m_renderer, column, (scr_h / 2), column, scr_h);

                // Drawing ceiling outside the map
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
                SDL_RenderDrawLine(m_renderer, column, 0, column, (scr_h / 2));
            }
        }   
    }

    void Renderer::loadTexture(const std::string& id, const std::string& path) {
        m_texture_manager->loadTexture(id, path);
    }

    void Renderer::renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2, bool x_flip, bool y_flip) {
        m_texture_manager->renderTexture(texture_id, x, y, render_width, render_height, cut_x1, cut_y1, cut_x2, cut_y2, x_flip, y_flip);
    }

    void Renderer::freeTexture(const std::string& id) {
        m_texture_manager->freeTexture(id);
    }

    void Renderer::setTextureToObjectId(int wall_id, const std::string& texture_id) {
        wall_texture_map[wall_id] = texture_id;
    }
    

}
