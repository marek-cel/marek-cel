#include <iostream>
#include <SDL.h>

using namespace std;

bool init();
bool loop();
void kill();

// Pointers to our window and surfaces
SDL_Window* window;
SDL_Surface* winSurface;

int main(int argc, char* args[])
{
	if ( !init() ) return 1;

	// Update window
	SDL_UpdateWindowSurface(window);

	while ( loop() )
	{
		// wait before processing the next frame
		SDL_Delay(10);
	}

	kill();

	return 0;
}

bool init()
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("sleep 1");
		return false;
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if ( !window )
	{
		cout << "Error creating window: " << SDL_GetError()  << endl;
		system("sleep 1");
		return false;
	}

	winSurface = SDL_GetWindowSurface(window);
	if ( !winSurface )
	{
		cout << "Error getting surface: " << SDL_GetError() << endl;
		system("sleep 1");
		return false;
	}
	return true;
}

bool loop()
{
	// Fill the window with a red rectangle
	SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 0, 0));

	SDL_Event e;
	while ( SDL_PollEvent(&e) )
	{
		if ( e.type == SDL_QUIT )
		{
			return false;
		}
	}

	// Update window
	SDL_UpdateWindowSurface(window);

	return true;
}

void kill()
{
	// Quit
	SDL_DestroyWindow(window);
	SDL_Quit();
}