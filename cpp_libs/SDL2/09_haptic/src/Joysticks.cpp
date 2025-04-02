#include <Joysticks.h>

#include <iostream>

void Joysticks::init()
{
	int joysticks_count = SDL_NumJoysticks();
	if ( joysticks_count == 0 )
	{
		std::cout << "No joysticks found." << std::endl;
	}
	else
	{
		std::cout << "Number of joysticks: " << joysticks_count << std::endl;
	}

	for ( int i = 0; i < joysticks_count; ++i )
	{
		SDL_Joystick* joystick = SDL_JoystickOpen(i);
		if ( joystick == nullptr )
		{
			std::cerr << "Error opening joystick " << i << ": " << SDL_GetError() << std::endl;
			continue;
		}

		SDL_JoystickID id = SDL_JoystickInstanceID(joystick);
		std::string name = SDL_JoystickName(joystick);
		int numAxes = SDL_JoystickNumAxes(joystick);
		int numButtons = SDL_JoystickNumButtons(joystick);
		int numHats = SDL_JoystickNumHats(joystick);

		std::cout << "Joystick " << i << ": " << name << " (ID: " << id << ")" << std::endl;
		std::cout << "  Axes: " << numAxes << ", Buttons: " << numButtons << ", Hats: " << numHats << std::endl;

		_joysticks.push_back(joystick);
	}
}
