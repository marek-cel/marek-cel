#include <iostream>
#include <SDL.h>

using namespace std;

bool init();
void kill();
bool load();

// Pointers to our window and surfaces
SDL_Window* window;
SDL_Surface* winSurface;
SDL_Surface* image;

int main(int argc, char* args[])
{

	if ( !init() ) return 1;
	if ( !load() ) return 1;

	// Blit image to entire window
	SDL_BlitSurface(image, NULL, winSurface, NULL);

	// Update window
	SDL_UpdateWindowSurface(window);
	system("sleep 1");

	kill();

	return 0;
}

bool load()
{
	// Load images
	SDL_Surface* temp = SDL_LoadBMP("../smiley.bmp");
	if ( !temp )
	{
		cout << "Error loading image: " << SDL_GetError() << endl;
		system("sleep 1");
		return false;
	}

	// Format surfaces
	image = SDL_ConvertSurface(temp, winSurface->format, 0);

	// Free temporary surfaces
	SDL_FreeSurface(temp);

	// Make sure format succeeded
	if ( !image ) {
		cout << "Error converting surface: " << SDL_GetError() << endl;
		system("sleep 1");
		return false;
	}

	return true;
}

bool init()
{
	// See last example for comments
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

void kill()
{
	// Free image
	SDL_FreeSurface(image);

	// Quit
	SDL_DestroyWindow(window);
	SDL_Quit();
}