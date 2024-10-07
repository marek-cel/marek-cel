#include <iostream>
#include <SDL.h>

int main(int argc, char* args[])
{
	std::cout << "Hello World!" << std::endl;

	// if ( SDL_Init(SDL_INIT_GAMECONTROLLER) < 0 ) {
	// 	std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	// 	return 1;
	// }

	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	int joystickCount = SDL_NumJoysticks();
	if ( joystickCount == 0 )
	{
		std::cout << "No joysticks found." << std::endl;
		SDL_Quit();
		return 0;
	}
	else
	{
		std::cout << "Number of joysticks: " << joystickCount << std::endl;
	}

	SDL_Joystick** joysticks = new SDL_Joystick*[joystickCount];

	for ( int i = 0; i < joystickCount; ++i )
	{
		joysticks[i] = SDL_JoystickOpen(i);
		if ( joysticks[i] == NULL )
		{
			std::cout << "Error opening joystick " << i << ": " << SDL_GetError() << std::endl;
		}
		else
		{
			std::cout << "Joystick " << i << " name: "    << SDL_JoystickName       (joysticks[i]) << std::endl;
			std::cout << "Joystick " << i << " axes: "    << SDL_JoystickNumAxes    (joysticks[i]) << std::endl;
			std::cout << "Joystick " << i << " buttons: " << SDL_JoystickNumButtons (joysticks[i]) << std::endl;
			std::cout << "Joystick " << i << " balls: "   << SDL_JoystickNumBalls   (joysticks[i]) << std::endl;
			std::cout << "Joystick " << i << " hats: "    << SDL_JoystickNumHats    (joysticks[i]) << std::endl;
			std::cout << "Joystick " << i << " vendor: "  << std::hex << SDL_JoystickGetVendor  (joysticks[i]) << std::endl;
			std::cout << "Joystick " << i << " product: " << std::hex << SDL_JoystickGetProduct (joysticks[i]) << std::endl;
			std::cout << std::dec; // Reset to decimal output
			std::cout << std::endl;
		}
	}

	bool quit = false;
	while ( !quit )
	{
		SDL_Event event;
		while ( SDL_PollEvent(&event) )
		{
			switch ( event.type )
			{
			case SDL_QUIT:
				std::cout << "Quit event." << std::endl;
				quit = true;
				break;

			case SDL_JOYAXISMOTION:
				std::cout << "Joystick " << event.jaxis.which << " axis " << (int)event.jaxis.axis << " value " << event.jaxis.value << std::endl;
				break;

			case SDL_JOYHATMOTION:
				std::cout << "Joystick " << event.jhat.which << " hat " << (int)event.jhat.hat << " value " << (int)event.jhat.value << std::endl;
				break;

			case SDL_JOYBUTTONDOWN:
				std::cout << "Joystick " << event.jbutton.which << " button " << (int)event.jbutton.button << " down" << std::endl;
				break;

			case SDL_JOYBUTTONUP:
				std::cout << "Joystick " << event.jbutton.which << " button " << (int)event.jbutton.button << " up" << std::endl;
				break;

			case SDL_JOYDEVICEADDED:
				std::cout << "Joystick " << event.jdevice.which << " added" << std::endl;
				break;

			case SDL_JOYDEVICEREMOVED:
				std::cout << "Joystick " << event.jdevice.which << " removed" << std::endl;
				break;

			default:
				break;
			}
		}
	}

	for ( int i = 0; i < joystickCount; ++i )
	{
		SDL_JoystickClose(joysticks[i]);
	}

	SDL_Quit();
	return 0;
}