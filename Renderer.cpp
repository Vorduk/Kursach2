#include "Renderer.h"

#define THROW_ENGINE_EXCEPTION(msg) throw engine::EngineException(msg, __FILE__, __LINE__, __func__) //< Macros.

namespace engine
{
    void Renderer::drawWallTextures(int wall_id, int axis, int column, int ceiling, int height, int texture_column, std::array<float, 3>& fog_factors)
    {
        // Get the texture ID for the given wall_id
        auto it = m_column_texture_map.find(wall_id);
        if (it != m_column_texture_map.end()) {
            std::string texture_id = it->second;

            int h = m_texture_sizes[texture_id].first;

            // Call renderTexture based on the axis
            if (axis == 0) { 
                renderTexture(texture_id, column, ceiling, column, height, texture_column, 0, texture_column + 1, h, false, false, fog_factors);
            }
            else { 
                renderTexture(texture_id, column, ceiling, column, height, texture_column, 0, texture_column + 1, h, false, false, fog_factors);
            }
        }
        else {
            // todo
        }
    }

    void Renderer::drawSkyBox(double ray_angle, int column) {
        double ray_angle_deg = ray_angle;
        std::string texture_id = "sky";

        int w = m_texture_sizes[texture_id].first;
        int h = m_texture_sizes[texture_id].second;

        if (ray_angle_deg < 0) {
            ray_angle_deg += (2 * M_PI);
        }
        if (ray_angle_deg > (2 * M_PI)) {
            ray_angle_deg -= (2 * M_PI);
        }

        double k = w / (M_PI * 2);
        double p_k = k * ray_angle_deg;
        int tex_col = static_cast<int>(p_k);

        std::array<float, 3> fog_factors = { 1.0, 1.0, 1.0 };

        renderTexture(texture_id, column, 0, w, h, tex_col, 0, tex_col + 1, h, false, false, fog_factors);
    }

    Renderer::Renderer(Window* window)
      : m_renderer(SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE)),
        m_width(window->getWidth()),
        m_height(window->getHeight()) {}

    Renderer::~Renderer()
	{
        clearTextures();
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

    void Renderer::setWallTexture(int wall_id, const std::string& texture_id) {
        m_column_texture_map[wall_id] = texture_id;
    }

    void Renderer::loadTexture(const std::string& id, const std::string& path) {
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (!loadedSurface) {
            std::string sdl_image_error = IMG_GetError();
            THROW_ENGINE_EXCEPTION("SDL_image failed: " + sdl_image_error + ".");
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);

        if (!texture) {
            std::string sdl_texture_error = SDL_GetError();
            THROW_ENGINE_EXCEPTION("Failed to create texture: " + sdl_texture_error + ".");
        }

        // Get texture sizes
        int width, height;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

        // Save texture and its size
        m_textures[id] = texture;
        m_texture_sizes[id] = std::make_pair(width, height);
    }

    void Renderer::renderTexture(const std::string& texture_id, int x, int y, int render_width, int render_height, int cut_x1, int cut_y1, int cut_x2, int cut_y2, bool x_flip, bool y_flip, std::array<float, 3>& fog_factors)
    {
        SDL_Texture* texture = m_textures[texture_id];
        if (texture) {
            // Define the area to render the texture
            SDL_Rect renderQuad = { x, y, render_width, render_height };

            // Define the clipping area
            SDL_Rect clip;
            clip.x = cut_x1;
            clip.y = cut_y1;
            clip.w = cut_x2 - cut_x1; // Ensure the width is correct
            clip.h = cut_y2 - cut_y1; // Ensure the height is correct

            // Determine flip flags
            SDL_RendererFlip flip = SDL_FLIP_NONE; // Initial value - no flip
            if (x_flip) {
                flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
            }
            if (y_flip) {
                flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
            }

            Uint8 r, g, b;
            SDL_GetTextureColorMod(texture, &r, &g, &b);

            // Set the new color modulation for darkening
            SDL_SetTextureColorMod(texture, static_cast<Uint8>(r * fog_factors[0]), static_cast<Uint8>(g * fog_factors[1]), static_cast<Uint8>(b * fog_factors[2]));

            // Set the new color modulation for darkening
            SDL_SetTextureColorMod(texture, static_cast<Uint8>(r * fog_factors[0]), static_cast<Uint8>(g * fog_factors[1]), static_cast<Uint8>(b * fog_factors[2]));

            // Render the texture with the specified clipping and flipping
            SDL_RenderCopyEx(m_renderer, texture, &clip, &renderQuad, 0.0, nullptr, flip);

            // Restore the original color modulation of the texture
            SDL_SetTextureColorMod(texture, r, g, b);
        }
        else {
            THROW_ENGINE_EXCEPTION("Texture with id " + texture_id + " not found.");
        }
    }
    
    void Renderer::freeTexture(const std::string& id) {
        if (m_textures.count(id)) {
            SDL_DestroyTexture(m_textures[id]);
            m_textures.erase(id);
        }
    }

    void Renderer::clearTextures() {
        for (auto& pair : m_textures) {
            SDL_DestroyTexture(pair.second);
        }
        m_textures.clear();
    }

    void Renderer::loadTexturesFromScene(Scene scene)
    {
        clearTextures();

        for (const auto& entry : scene.getTexturesPredefine()) {
            const auto& key = entry.first; // std::pair<int, std::string>
            const std::string& path = entry.second; 

            std::string id = key.second;

            loadTexture(id, "textures/" + path);
            setWallTexture(key.first, key.second);
        }
    }

	void Renderer::renderSceneDDA(Scene* scene)
	{
        int gridSizeX = scene->getObstacleSizeX();
        int gridSizeY = scene->getObstacleSizeY();

        Camera cur_camera = scene->getCamera();

        int rays_n = m_width;

        double cam_angle = cur_camera.getCameraAngle();
        double cam_fov = cur_camera.getFov();
        double cam_x = cur_camera.getCameraX();
        double cam_y = cur_camera.getCameraY();
        double render_distance = cur_camera.getRenderDistance();

        double prev_distance;

        std::vector<double> distances;

        for (int column = 0; column < rays_n; column++) {    
            int is_corner = 0;

            int scr_h = m_height;

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
                    hit = scene->getObstacle(map_check_x, map_check_y);
                    if (hit != 0) {
                        if ((fabs(dot_x - round(dot_x)) < 0.008) && (fabs(dot_y - round(dot_y)) < 0.008)) {
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

            drawSkyBox(ray_angle, column);

            prev_distance = cur_distance;
            distances.push_back(cur_distance);

            if (hit != 0) {

                double n_c = cur_distance * cos(ray_angle - cam_angle); ///< Distance with fish eye fix

                double fog_factor = 3.0 / n_c;
                if (fog_factor > 1.0) {
                    fog_factor = 1.0; // Limit the value to 1.0
                }
                else if (fog_factor < 0.0) {
                    fog_factor = 0.0; // Limit the value to 0.0
                }
                std::array<float, 3> fog_factors = { 1.0, fog_factor, fog_factor };

                int ceiling = (double)(scr_h / 2) - (scr_h / n_c); ///< Ceiling height on the screen

                // What side of wall?
                double test_x = (double)dot_x - (int)dot_x;
                double test_y = (double)dot_y - (int)dot_y;

                int height = scr_h - (2 * ceiling);

                auto it = m_column_texture_map.find(hit);
                std::string cur_tex_id = it->second;
                int w = m_texture_sizes[cur_tex_id].first;

                // Drawing wall
                if (test_x > 0.00001)
                {
                    int tex_col = round(((double)dot_x - (int)dot_x) * w);
                    drawWallTextures(hit, 0, column, ceiling, height, tex_col, fog_factors);
                }

                if (test_y > 0.00001)
                {
                    int tex_col = round(((double)dot_y - (int)dot_y) * w);
                    drawWallTextures(hit, 1, column, ceiling, height, tex_col, fog_factors);
                }

                if (is_corner) {
                    SDL_SetRenderDrawColor(m_renderer, 100 * fog_factor, 100 * fog_factor, 100 * fog_factor, 255);
                    SDL_RenderDrawLine(m_renderer, column, ceiling, column, scr_h - ceiling);
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
            }

        } 

        int fov_c = (cam_fov * 180) / M_PI;

        for (Enemy* enemy : scene->getEnemies()) {

            float sprite_dir = atan2(enemy->getY() - cam_y, enemy->getX() - cam_x);
            while (sprite_dir - cam_angle > M_PI) sprite_dir -= 2 * M_PI;
            while (sprite_dir - cam_angle < -M_PI) sprite_dir += 2 * M_PI;

            float sprite_dist = scene->calculateDistance(enemy);

            double fog_factor = 3.0 / sprite_dist;
            if (fog_factor > 1.0) {
                fog_factor = 1.0; // Limit the value to 1.0
            }
            else if (fog_factor < 0.0) {
                fog_factor = 0.0; // Limit the value to 0.0
            }
            std::array<float, 3> fog_factors = { 1.0, fog_factor, fog_factor };

            size_t sprite_screen_size = std::min(2000, static_cast<int>(m_height / sprite_dist));

            float sprite_angle = sprite_dir - cam_angle;

            SDL_Color color11 = { 255, 255, 255, 255 };

            int center = ((m_width / cam_fov) * sprite_angle) + (m_width / 2);
            int start1 = center - sprite_screen_size / 2;
            int finish1 = center + sprite_screen_size / 2;

            int start = start1 < 0 ? 0 : start1;
            int finish = finish1;

            if (finish > 0) {

                finish = finish >= m_width ? m_width-1 : finish;

                for (int i = start; i <= finish; i++) {
                    int tex_col = ((i - start1) * 256) / (finish1 - start1);

                    if (sprite_dist < distances[i]) {
                        renderTexture("ololo", i, (m_height / 2), 1, sprite_screen_size, tex_col, 0, tex_col+1, 256, false, false, fog_factors);
                    }
                    
                }
            }

        }

    }

} // engine
