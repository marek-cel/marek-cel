#include <iostream>
#include <cstdio>

#include <SDL.h>

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    SDL_Window* window = nullptr;

    SDL_Surface* screenSurface = nullptr;

    // Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create window
    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if( window == nullptr )
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    //Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    //Fill the surface white
    SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    //Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait for a few seconds to see the window (replace with your own event loop as needed)
    SDL_Delay(3000);

    return 0;
}