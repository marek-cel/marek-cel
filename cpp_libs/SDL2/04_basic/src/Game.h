#pragma once

#include <SDL.h>

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return _isRunning; }

private:

    bool _isRunning = false;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};