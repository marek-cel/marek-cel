#include <Controllers.h>

#include <iostream>

#include <SDL_haptic.h>

void Controllers::init()
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
		Controller joystick;
		joystick.joystick = SDL_JoystickOpen(i);
		if ( joystick.joystick == nullptr )
		{
			std::cerr << "Error opening joystick " << i << ": " << SDL_GetError() << std::endl;
			continue;
		}

		joystick.name = SDL_JoystickName(joystick.joystick);
		joystick.id = SDL_JoystickInstanceID(joystick.joystick);
		joystick.num_axes = SDL_JoystickNumAxes(joystick.joystick);
		joystick.num_buttons = SDL_JoystickNumButtons(joystick.joystick);
		joystick.num_hats = SDL_JoystickNumHats(joystick.joystick);
		joystick.vendor = SDL_JoystickGetVendor(joystick.joystick);
		joystick.product = SDL_JoystickGetProduct(joystick.joystick);
		joystick.has_haptic = SDL_JoystickIsHaptic(joystick.joystick);
		_controllers.push_back(joystick);
	}
}

void Controllers::update()
{
	SDL_Event event;
	while ( SDL_PollEvent(&event) )
	{
		switch ( event.type )
		{
		case SDL_JOYAXISMOTION:
			_controllers[event.jaxis.which].axes[event.jaxis.axis] = event.jaxis.value / kAxisRange;
			std::cout << "Joystick " << event.jaxis.which << " axis " << (int)event.jaxis.axis << " value " << event.jaxis.value << std::endl;
			break;

		case SDL_JOYHATMOTION:
			std::cout << "Joystick " << event.jhat.which << " hat " << (int)event.jhat.hat << " value " << (int)event.jhat.value << std::endl;
			break;

		case SDL_JOYBUTTONDOWN:
			_controllers[event.jbutton.which].buttons[event.jbutton.button] = true;
			std::cout << "Joystick " << event.jbutton.which << " button " << (int)event.jbutton.button << " down" << std::endl;
			break;

		case SDL_JOYBUTTONUP:
			_controllers[event.jbutton.which].buttons[event.jbutton.button] = false;
			std::cout << "Joystick " << event.jbutton.which << " button " << (int)event.jbutton.button << " up" << std::endl;
			break;

		case SDL_JOYDEVICEADDED:
			std::cout << "Joystick " << event.jdevice.which << " added" << std::endl;
			break;

		case SDL_JOYDEVICEREMOVED:
			// Remove the joystick from the list of controllers
			for ( auto it = _controllers.begin(); it != _controllers.end(); ++it )
			{
				if ( it->id == event.jdevice.which )
				{
					SDL_JoystickClose(it->joystick);
					_controllers.erase(it);
					break;
				}
			}
			std::cout << "Joystick " << event.jdevice.which << " removed" << std::endl;
			break;

		default:
			break;
		}
	}
}
