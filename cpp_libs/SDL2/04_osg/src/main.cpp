#include <iostream>

#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <SDL.h>

#include <KeyMap.h>
#include <cgi/SceneRoot.h>

SDL_Window* window;
SDL_Renderer* renderer;

void init(const char *title, int xpos, int ypos, int width, int height);
void clean();

int main(int argc, char* args[])
{
	const int fps = 60;
	const int frameDelay = 1000 / fps;

	const int width = 800;
	const int height = 600;

	std::cout << "Hello World" << std::endl;

	init("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);

	SceneRoot sceneRoot;
	osgViewer::Viewer viewer;
    osgViewer::GraphicsWindowEmbedded* gw = viewer.setUpViewerAsEmbeddedInWindow(0,0,width,height);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.setKeyEventSetsDone(0);

	viewer.realize();

	viewer.setSceneData(sceneRoot.getRootNode());

	Uint32 frameStart;
	int frameTime;

	bool done = false;
	while (!done)
	{
		frameStart = SDL_GetTicks();

		auto eventQueue = gw->getEventQueue();
		SDL_Event e;
		while ( SDL_PollEvent(&e) )
		{
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				eventQueue->mouseMotion(e.motion.x, e.motion.y);
				break;

			case SDL_MOUSEBUTTONDOWN:
				eventQueue->mouseButtonPress(e.button.x, e.button.y, e.button.button);
				break;

			case SDL_MOUSEBUTTONUP:
				eventQueue->mouseButtonRelease(e.button.x, e.button.y, e.button.button);
				break;

			case SDL_KEYDOWN:
				eventQueue->keyPress(convertKeyFromSdlToOsg(e.key.keysym));
				break;

			case SDL_KEYUP:
				eventQueue->keyRelease(convertKeyFromSdlToOsg(e.key.keysym));
				break;

			case SDL_WINDOWEVENT:
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					eventQueue->windowResize(0, 0, e.window.data1, e.window.data2);
					gw->resized(0, 0, e.window.data1, e.window.data2);
					break;
				}

				break;

			case SDL_QUIT:
				std::cout << "Quit event" << std::endl;
				done = true;
				break;
			}
		}

		viewer.frame();

        // Swap Buffers
        SDL_GL_SwapWindow(window);

		// frameTime = SDL_GetTicks() - frameStart;
		// if (frameDelay > frameTime)
		// {
		// 	SDL_Delay(frameDelay - frameTime);
		// }
	}

	clean();

	return 0;
}

void init(const char *title, int xpos, int ypos, int width, int height)
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

    window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if ( !window )
	{
		std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
	}

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if ( !renderer )
    {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    }

	//SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
}

void clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
	SDL_Quit();
    std::cout << "Bye!" << std::endl;
}
