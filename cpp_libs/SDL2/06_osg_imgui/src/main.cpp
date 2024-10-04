#include <iostream>

#include <GL/gl.h>

#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <KeyMap.h>
#include <cgi/SceneRoot.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_GLContext gl_context;

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		 // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    //ImGui_ImplOpenGL3_Init("#version 100");
	ImGui_ImplOpenGL3_Init();

	// OSG
	SceneRoot sceneRoot;
	osgViewer::Viewer viewer;
    osgViewer::GraphicsWindowEmbedded* gw = viewer.setUpViewerAsEmbeddedInWindow(0,0,width,height);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	viewer.addEventHandler(new osgViewer::StatsHandler);
	//viewer.getEventHandlers().push_front(new mc::gui::ImGuiApp);
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
			ImGui_ImplSDL2_ProcessEvent(&e);

			// disable OSG event handling when interacting with ImGui
			if (!ImGui::GetIO().WantCaptureMouse && !ImGui::GetIO().WantCaptureKeyboard)
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
				}
			}

			switch (e.type)
			{
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
        //SDL_GL_SwapWindow(window);


        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        constexpr ImGuiDockNodeFlags dockspace_flags =
            ImGuiDockNodeFlags_NoDockingInCentralNode | ImGuiDockNodeFlags_PassthruCentralNode;
        //constexpr ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGuiID dockSpaceId = ImGui::GetID("MyDockSpace");
        dockSpaceId = ImGui::DockSpaceOverViewport(dockSpaceId, ImGui::GetMainViewport(), dockspace_flags);

		bool open = true;
		ImGui::ShowDemoWindow(&open);

		// Rendering
        ImGui::Render();
        //glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        //glClearColor(0.0, 0.0, 0.0, 1.0);
        //glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
	else
	{
		gl_context = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, gl_context);
		SDL_GL_SetSwapInterval(1); // Enable vsync
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
