#include <iostream>

#include <Game.h>

using namespace std;

int main(int argc, char* args[])
{
	std::cout << "Hello World" << std::endl;

	Game game;
	game.init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false);

	while (game.running())
	{
		game.handleEvents();
		game.update();
		game.render();
	}

	game.clean();

	return 0;
}
