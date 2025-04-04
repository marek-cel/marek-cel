#include <iostream>
#include <memory>

#include <QApplication>

#include <SDL.h>

#include <MainWindow.h>

int main(int argc, char* argv[])
{
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

    QApplication app(argc, argv);

    MainWindow win;
    win.show();
    win.init();

    int result = app.exec();

    SDL_Quit();

    return result;
}
