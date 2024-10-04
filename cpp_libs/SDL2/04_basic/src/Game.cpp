#include "Game.h"

#include <iostream>

Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

    if (fullscreen)
    {
        _window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_FULLSCREEN);
    }
    else
    {
	    _window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    }

	if ( !_window )
	{
		std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
        return;
	}

    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if ( !_renderer )
    {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    }
    else
    {
        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
        _isRunning = true;
    }
}

void Game::handleEvents()
{
    SDL_Event e;
	while ( SDL_PollEvent(&e) )
	{
		if ( e.type == SDL_QUIT )
		{
			std::cout << "Quit event" << std::endl;
			_isRunning = false;
		}
	}
}

void Game::update()
{
}

void Game::render()
{
}

void Game::clean()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
	SDL_Quit();
    std::cout << "Bye!" << std::endl;
}
