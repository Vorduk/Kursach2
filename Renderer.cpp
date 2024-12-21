#include "Renderer.h"

namespace engine
{
	Renderer::Renderer(SDL_Window* window)
	{
		m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
}
