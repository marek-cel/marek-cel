#include <iostream>
#include <SDL.h>

SDL_GameController** controllers = nullptr;

void rumble();
void setLED();

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

	controllers = new SDL_GameController*[joystickCount];

	for ( int i = 0; i < joystickCount; ++i )
	{
		controllers[i] = SDL_GameControllerOpen(i);
		if ( controllers[i] == NULL )
		{
			std::cout << "Error opening joystick " << i << ": " << SDL_GetError() << std::endl;
		}
		else
		{
			std::cout << "Joystick " << i << " name: " << SDL_GameControllerName(controllers[i]) << std::endl;

			std::cout << "Joystick " << i << " axes: "    << SDL_JoystickNumAxes    (SDL_GameControllerGetJoystick(controllers[i])) << std::endl;
			std::cout << "Joystick " << i << " buttons: " << SDL_JoystickNumButtons (SDL_GameControllerGetJoystick(controllers[i])) << std::endl;
			std::cout << "Joystick " << i << " balls: "   << SDL_JoystickNumBalls   (SDL_GameControllerGetJoystick(controllers[i])) << std::endl;
			std::cout << "Joystick " << i << " hats: "    << SDL_JoystickNumHats    (SDL_GameControllerGetJoystick(controllers[i])) << std::endl;

			std::cout << "Joystick " << i << " instance id: " << SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controllers[i])) << std::endl;
			std::cout << "Joystick " << i << " product version: " << SDL_GameControllerGetProductVersion(controllers[i]) << std::endl;
			std::cout << "Joystick " << i << " type: " << SDL_GameControllerGetType(controllers[i]) << std::endl;
			std::cout << "Joystick " << i << " vendor: " << SDL_GameControllerGetVendor(controllers[i]) << std::endl;
			std::cout << "Joystick " << i << " product: " << SDL_GameControllerGetProduct(controllers[i]) << std::endl;
			SDL_JoystickGUID guid = SDL_JoystickGetGUID(SDL_GameControllerGetJoystick(controllers[i]));
			char guidString[128];
			SDL_JoystickGetGUIDString(guid, guidString, 128);
			std::cout << "Joystick " << i << " GUID: " << guidString << std::endl;

			std::cout << "Joystick " << i << " has rumble: " << SDL_GameControllerHasRumble(controllers[i]) << std::endl;
			std::cout << "Joystick " << i << " has rumble triggers: " << SDL_GameControllerHasRumbleTriggers(controllers[i]) << std::endl;

			std::cout << "Joystick " << i << " has led: " << SDL_GameControllerHasLED(controllers[i]) << std::endl;

			std::cout << std::endl;
		}
	}

	rumble();
	setLED();

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
				rumble();
				setLED();
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
		SDL_GameControllerClose(controllers[i]);
	}

	if ( controllers != nullptr )
	{
		delete[] controllers;
		controllers = nullptr;
	}

	SDL_Quit();
	return 0;
}

void rumble()
{
	if ( SDL_GameControllerHasRumble(controllers[0]) )
	{
		std::cout << "Rumbling joystick 0" << std::endl;
		SDL_GameControllerRumble(controllers[0], 0xFFFF, 0xFFFF, 1000);
	}
}

void setLED()
{
	if ( SDL_GameControllerHasLED(controllers[0]) )
	{
		std::cout << "Setting LED color for joystick 0" << std::endl;
		SDL_GameControllerSetLED(controllers[0], 0xFF, 0x00, 0x00);
	}
}