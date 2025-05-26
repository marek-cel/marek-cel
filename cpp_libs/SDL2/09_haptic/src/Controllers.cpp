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

		int num_axes = SDL_JoystickNumAxes(joystick.joystick);
		int num_buttons = SDL_JoystickNumButtons(joystick.joystick);
		int num_hats = SDL_JoystickNumHats(joystick.joystick);
		std::cout << "Joystick " << i << ": " << SDL_JoystickName(joystick.joystick) << std::endl;
		std::cout << "  Number of axes: " << num_axes << std::endl;
		std::cout << "  Number of buttons: " << num_buttons << std::endl;
		std::cout << "  Number of hats: " << num_hats << std::endl;

		SDL_JoystickType type = SDL_JoystickGetDeviceType(i);
		switch ( type )
		{
		case SDL_JOYSTICK_TYPE_GAMECONTROLLER:
			std::cout << "Joystick " << i << " is a GAME CONTROLLER." << std::endl;
			break;
		case SDL_JOYSTICK_TYPE_WHEEL:
			std::cout << "Joystick " << i << " is a WHEEL." << std::endl;
			break;
		case SDL_JOYSTICK_TYPE_ARCADE_STICK:
			std::cout << "Joystick " << i << " is an ARCADE STICK." << std::endl;
			break;
		case SDL_JOYSTICK_TYPE_FLIGHT_STICK:
			std::cout << "Joystick " << i << " is a FLIGHT STICK." << std::endl;
			break;
		case SDL_JOYSTICK_TYPE_DANCE_PAD:
			std::cout << "Joystick " << i << " is a DANCE PAD." << std::endl;
			break;
		case SDL_JOYSTICK_TYPE_GUITAR:
			std::cout << "Joystick " << i << " is a GUITAR." << std::endl;
			break;
		case SDL_JOYSTICK_TYPE_DRUM_KIT:
			std::cout << "Joystick " << i << " is a DRUM KIT." << std::endl;
			break;
		case SDL_JOYSTICK_TYPE_ARCADE_PAD:
			std::cout << "Joystick " << i << " is an ARCADE PAD." << std::endl;
			break;
		case SDL_JOYSTICK_TYPE_THROTTLE:
			std::cout << "Joystick " << i << " is a THROTTLE." << std::endl;
			break;
		default:
			std::cout << "Joystick " << i << " is of UNKNOWN TYPE." << std::endl;
			break;
		}

		joystick.name = SDL_JoystickName(joystick.joystick);
		joystick.id = SDL_JoystickInstanceID(joystick.joystick);
		joystick.num_axes = SDL_JoystickNumAxes(joystick.joystick);
		joystick.num_buttons = SDL_JoystickNumButtons(joystick.joystick);
		joystick.num_hats = SDL_JoystickNumHats(joystick.joystick);
		joystick.vendor = SDL_JoystickGetVendor(joystick.joystick);
		joystick.product = SDL_JoystickGetProduct(joystick.joystick);
		joystick.has_haptic = SDL_JoystickIsHaptic(joystick.joystick);

		std::cout << "Vendor ID: " << joystick.vendor << " Product ID: " << joystick.product << std::endl;

        if ( joystick.has_haptic )
		{
			std::cout << "Joystick " << i << " has haptic feedback." << std::endl;

			joystick.haptic = SDL_HapticOpenFromJoystick(joystick.joystick);
			if ( joystick.haptic == nullptr )
			{
				std::cerr << "Error opening haptic device: " << SDL_GetError() << std::endl;
				SDL_JoystickClose(joystick.joystick);
				continue;
			}

			int supported_effects = SDL_HapticQuery(joystick.haptic);
			if ( supported_effects < 0 )
			{
				std::cerr << "Error querying haptic device: " << SDL_GetError() << std::endl;
				SDL_HapticClose(joystick.haptic);
				SDL_JoystickClose(joystick.joystick);
				continue;
			}

			joystick.has_constant_effect = (supported_effects & SDL_HAPTIC_CONSTANT) != 0;
			if ( joystick.has_constant_effect )
			{
				std::cout << "Joystick " << i << " supports constant effect." << std::endl;
				joystick.constant_effect_id = initConstantEffect(joystick.haptic, &joystick.constant_effect);
			}

			joystick.has_sine_wave_effect = (supported_effects & SDL_HAPTIC_SINE) != 0;
			if ( joystick.has_sine_wave_effect )
			{
				std::cout << "Joystick " << i << " supports sine wave effect." << std::endl;
				initPeriodicEffect(&joystick.sine_wave_effect, SDL_HAPTIC_SINE);
			}

			joystick.has_left_right_effect = (supported_effects & SDL_HAPTIC_LEFTRIGHT) != 0;
			if ( joystick.has_left_right_effect )
			{
				std::cout << "Joystick " << i << " supports left/right effect." << std::endl;
				initPeriodicEffect(&joystick.left_right_effect, SDL_HAPTIC_LEFTRIGHT);
			}

			joystick.has_triangle_wave_effect = (supported_effects & SDL_HAPTIC_TRIANGLE) != 0;
			if ( joystick.has_triangle_wave_effect )
			{
				std::cout << "Joystick " << i << " supports triangle wave effect." << std::endl;
				initPeriodicEffect(&joystick.triangle_wave_effect, SDL_HAPTIC_TRIANGLE);
			}

			joystick.has_sawtooth_up_effect = (supported_effects & SDL_HAPTIC_SAWTOOTHUP) != 0;
			if ( joystick.has_sawtooth_up_effect )
			{
				std::cout << "Joystick " << i << " supports sawtooth up effect." << std::endl;
				initPeriodicEffect(&joystick.sawtooth_up_effect, SDL_HAPTIC_SAWTOOTHUP);
			}

			joystick.has_sawtooth_dn_effect = (supported_effects & SDL_HAPTIC_SAWTOOTHDOWN) != 0;
			if ( joystick.has_sawtooth_dn_effect )
			{
				std::cout << "Joystick " << i << " supports sawtooth down effect." << std::endl;
				initPeriodicEffect(&joystick.sawtooth_dn_effect, SDL_HAPTIC_SAWTOOTHDOWN);
			}

			joystick.has_periodic_effect = joystick.has_sine_wave_effect
				|| joystick.has_left_right_effect
				|| joystick.has_triangle_wave_effect
				|| joystick.has_sawtooth_up_effect
				|| joystick.has_sawtooth_dn_effect;

			joystick.has_ramp_effect = (supported_effects & SDL_HAPTIC_RAMP) != 0;
			if ( joystick.has_ramp_effect )
			{
				std::cout << "Joystick " << i << " supports ramp effect." << std::endl;
				// joystick.ramp_effect_id = initConstantEffect(joystick.haptic, &joystick.ramp_effect);
			}

			joystick.has_springs_effect = (supported_effects & SDL_HAPTIC_SPRING) != 0;
			if ( joystick.has_springs_effect )
			{
				std::cout << "Joystick " << i << " supports springs effect." << std::endl;
				// joystick.springs_effect_id = initConstantEffect(joystick.haptic, &joystick.springs_effect);
			}

			joystick.has_dampers_effect = (supported_effects & SDL_HAPTIC_DAMPER) != 0;
			if ( joystick.has_dampers_effect )
			{
				std::cout << "Joystick " << i << " supports dampers effect." << std::endl;
				// joystick.dampers_effect_id = initConstantEffect(joystick.haptic, &joystick.dampers_effect);
			}

			joystick.has_inertia_effect = (supported_effects & SDL_HAPTIC_INERTIA) != 0;
			if ( joystick.has_inertia_effect )
			{
				std::cout << "Joystick " << i << " supports inertia effect." << std::endl;
				// joystick.inertia_effect_id = initConstantEffect(joystick.haptic, &joystick.inertia_effect);
			}

			joystick.has_friction_effect = (supported_effects & SDL_HAPTIC_FRICTION) != 0;
			if ( joystick.has_friction_effect )
			{
				std::cout << "Joystick " << i << " supports friction effect." << std::endl;
				// joystick.friction_effect_id = initConstantEffect(joystick.haptic, &joystick.friction_effect);
			}
		}

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
			// std::cout << "Joystick " << event.jaxis.which << " axis " << (int)event.jaxis.axis << " value " << event.jaxis.value << std::endl;
			break;

		case SDL_JOYHATMOTION:
			// std::cout << "Joystick " << event.jhat.which << " hat " << (int)event.jhat.hat << " value " << (int)event.jhat.value << std::endl;
			break;

		case SDL_JOYBUTTONDOWN:
			_controllers[event.jbutton.which].buttons[event.jbutton.button] = true;
			// std::cout << "Joystick " << event.jbutton.which << " button " << (int)event.jbutton.button << " down" << std::endl;
			break;

		case SDL_JOYBUTTONUP:
			_controllers[event.jbutton.which].buttons[event.jbutton.button] = false;
			// std::cout << "Joystick " << event.jbutton.which << " button " << (int)event.jbutton.button << " up" << std::endl;
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

void Controllers::stopAllEffects()
{
	for ( auto& controller : _controllers )
	{
		if ( controller.haptic )
		{
			SDL_HapticStopAll(controller.haptic);

			if ( controller.sine_wave_effect_id >= 0 )
			{
				SDL_HapticDestroyEffect(controller.haptic, controller.sine_wave_effect_id);
				controller.sine_wave_effect_id = -1;
			}

			if ( controller.left_right_effect_id >= 0 )
			{
				SDL_HapticDestroyEffect(controller.haptic, controller.left_right_effect_id);
				controller.left_right_effect_id = -1;
			}

			if ( controller.triangle_wave_effect_id >= 0 )
			{
				SDL_HapticDestroyEffect(controller.haptic, controller.triangle_wave_effect_id);
				controller.triangle_wave_effect_id = -1;
			}

			if ( controller.sawtooth_up_effect_id >= 0 )
			{
				SDL_HapticDestroyEffect(controller.haptic, controller.sawtooth_up_effect_id);
				controller.sawtooth_up_effect_id = -1;
			}

			if ( controller.sawtooth_dn_effect_id >= 0 )
			{
				SDL_HapticDestroyEffect(controller.haptic, controller.sawtooth_dn_effect_id);
				controller.sawtooth_dn_effect_id = -1;
			}
		}
	}
}

void Controllers::startConstantForce(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( ctrl.constant_effect_id < 0 )
	{
		std::cout << "Starting Constant Force on joystick " << index << " failed" << std::endl;
		return;
	}

	SDL_HapticRunEffect(ctrl.haptic, _controllers[index].constant_effect_id, 1);
}


void Controllers::updateConstantForce(unsigned int index, double force_x, double force_y)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( ctrl.constant_effect_id < 0 )
	{
		std::cerr << "Constant effect not initialized for joystick " << index << std::endl;
		return;
	}
	double net_force = sqrt(force_x * force_x + force_y * force_y);

	// TODO:: fix direction

	ctrl.constant_effect.constant.level = static_cast<int>(net_force * 0x7FFF); // Scale to 16-bit signed integer
	ctrl.constant_effect.constant.direction.dir[0] = static_cast<int>(force_x * 0x7FFF);
	ctrl.constant_effect.constant.direction.dir[1] = static_cast<int>(force_y * 0x7FFF);
	ctrl.constant_effect.constant.direction.dir[2] = 0; // Not used for constant effect

	SDL_HapticUpdateEffect(ctrl.haptic, ctrl.constant_effect_id, &ctrl.constant_effect);
}

void Controllers::stopConstantForce(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( ctrl.constant_effect_id < 0 )
	{
		std::cout << "Stopping Constant Force on joystick " << index << " failed" << std::endl;
		return;
	}

	SDL_HapticStopEffect(ctrl.haptic, ctrl.constant_effect_id);
}

void Controllers::startSineWave(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( !ctrl.has_sine_wave_effect )
	{
		std::cout << "Starting Sine Wave on joystick " << index << " failed" << std::endl;
		return;
	}

	ctrl.sine_wave_effect_id = SDL_HapticNewEffect(ctrl.haptic, &ctrl.sine_wave_effect);
	if ( ctrl.sine_wave_effect_id < 0 )
	{
		std::cerr << "Error creating haptic effect: " << SDL_GetError() << std::endl;
	}

	SDL_HapticRunEffect(ctrl.haptic, ctrl.sine_wave_effect_id, 1);
	std::cout << "Starting Sine Wave on joystick " << index << std::endl;
	std::cout << "   magnitude: " << ctrl.sine_wave_effect.periodic.magnitude << std::endl;
	std::cout << "   period: " << ctrl.sine_wave_effect.periodic.period << std::endl;
}

void Controllers::updateSineWave(unsigned int index, double period, double magnitude)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];

	ctrl.sine_wave_effect.periodic.period = static_cast<int>(period * 1000); // Scale to 16-bit signed integer
	ctrl.sine_wave_effect.periodic.magnitude = static_cast<int>(magnitude * 32767); // Scale to 16-bit signed integer
}

void Controllers::stopSineWave(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( ctrl.sine_wave_effect_id < 0 )
	{
		std::cout << "Stopping Sine Wave on joystick " << index << " failed" << std::endl;
		return;
	}

	SDL_HapticStopEffect(ctrl.haptic, ctrl.sine_wave_effect_id);
	SDL_HapticDestroyEffect(ctrl.haptic, ctrl.sine_wave_effect_id);
	ctrl.sine_wave_effect_id = -1;
	std::cout << "Stopping Sine Wave on joystick " << index << std::endl;
}

void Controllers::startLeftRight(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( !ctrl.has_left_right_effect )
	{
		std::cout << "Starting Left/Right on joystick " << index << " failed" << std::endl;
		return;
	}

	ctrl.left_right_effect_id = SDL_HapticNewEffect(ctrl.haptic, &ctrl.left_right_effect);
	if ( ctrl.left_right_effect_id < 0 )
	{
		std::cerr << "Error creating haptic effect: " << SDL_GetError() << std::endl;
	}

	SDL_HapticRunEffect(ctrl.haptic, ctrl.left_right_effect_id, 1);
	std::cout << "Starting Left/Right on joystick " << index << std::endl;
	std::cout << "   magnitude: " << ctrl.left_right_effect.periodic.magnitude << std::endl;
	std::cout << "   period: " << ctrl.left_right_effect.periodic.period << std::endl;
}

void Controllers::updateLeftRight(unsigned int index, double period, double magnitude)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];

	ctrl.left_right_effect.periodic.period = static_cast<int>(period * 1000); // Scale to milliseconds
	ctrl.left_right_effect.periodic.magnitude = static_cast<int>(magnitude * 32767); // Scale to 16-bit signed integer
}

void Controllers::stopLeftRight(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( ctrl.left_right_effect_id < 0 )
	{
		std::cout << "Stopping Left/Right on joystick " << index << " failed" << std::endl;
		return;
	}

	SDL_HapticStopEffect(ctrl.haptic, ctrl.left_right_effect_id);
	SDL_HapticDestroyEffect(ctrl.haptic, ctrl.left_right_effect_id);
	ctrl.left_right_effect_id = -1;
	std::cout << "Stopping Left/Right on joystick " << index << std::endl;
}

void Controllers::startTriangularWave(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( !ctrl.has_triangle_wave_effect )
	{
		std::cout << "Starting Triangular Wave on joystick " << index << " failed" << std::endl;
		return;
	}

	ctrl.triangle_wave_effect_id = SDL_HapticNewEffect(ctrl.haptic, &ctrl.triangle_wave_effect);
	if ( ctrl.triangle_wave_effect_id < 0 )
	{
		std::cerr << "Error creating haptic effect: " << SDL_GetError() << std::endl;
	}

	SDL_HapticRunEffect(ctrl.haptic, ctrl.triangle_wave_effect_id, 1);
	std::cout << "Starting Triangular Wave on joystick " << index << std::endl;
	std::cout << "   magnitude: " << ctrl.triangle_wave_effect.periodic.magnitude << std::endl;
	std::cout << "   period: " << ctrl.triangle_wave_effect.periodic.period << std::endl;
}

void Controllers::updateTriangularWave(unsigned int index, double period, double magnitude)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];

	ctrl.triangle_wave_effect.periodic.period = static_cast<int>(period * 1000); // Scale to milliseconds
	ctrl.triangle_wave_effect.periodic.magnitude = static_cast<int>(magnitude * 32767); // Scale to 16-bit signed integer
}

void Controllers::stopTriangularWave(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( ctrl.triangle_wave_effect_id < 0 )
	{
		std::cout << "Stopping Triangular Wave on joystick " << index << " failed" << std::endl;
		return;
	}

	SDL_HapticStopEffect(ctrl.haptic, ctrl.triangle_wave_effect_id);
	SDL_HapticDestroyEffect(ctrl.haptic, ctrl.triangle_wave_effect_id);
	ctrl.triangle_wave_effect_id = -1;
	std::cout << "Stopping Triangular Wave on joystick " << index << std::endl;
}

void Controllers::startSawtoothUp(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( !ctrl.has_sawtooth_up_effect )
	{
		std::cout << "Starting Sawtooth Up on joystick " << index << " failed" << std::endl;
		return;
	}

	ctrl.sawtooth_up_effect_id = SDL_HapticNewEffect(ctrl.haptic, &ctrl.sawtooth_up_effect);
	if ( ctrl.sawtooth_up_effect_id < 0 )
	{
		std::cerr << "Error creating haptic effect: " << SDL_GetError() << std::endl;
	}

	SDL_HapticRunEffect(ctrl.haptic, ctrl.sawtooth_up_effect_id, 1);
	std::cout << "Starting Sawtooth Up on joystick " << index << std::endl;
	std::cout << "   magnitude: " << ctrl.sawtooth_up_effect.periodic.magnitude << std::endl;
	std::cout << "   period: " << ctrl.sawtooth_up_effect.periodic.period << std::endl;
}

void Controllers::updateSawtoothUp(unsigned int index, double period, double magnitude)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];

	ctrl.sawtooth_up_effect.periodic.period = static_cast<int>(period * 1000); // Scale to milliseconds
	ctrl.sawtooth_up_effect.periodic.magnitude = static_cast<int>(magnitude * 32767); // Scale to 16-bit signed integer
}

void Controllers::stopSawtoothUp(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( ctrl.sawtooth_up_effect_id < 0 )
	{
		std::cout << "Stopping Sawtooth Up on joystick " << index << " failed" << std::endl;
		return;
	}

	SDL_HapticStopEffect(ctrl.haptic, ctrl.sawtooth_up_effect_id);
	SDL_HapticDestroyEffect(ctrl.haptic, ctrl.sawtooth_up_effect_id);
	ctrl.sawtooth_up_effect_id = -1;
	std::cout << "Stopping Sawtooth Up on joystick " << index << std::endl;
}

void Controllers::startSawtoothDn(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( !ctrl.has_sawtooth_dn_effect )
	{
		std::cout << "Starting Sawtooth Down on joystick " << index << " failed" << std::endl;
		return;
	}

	ctrl.sawtooth_dn_effect_id = SDL_HapticNewEffect(ctrl.haptic, &ctrl.sawtooth_dn_effect);
	if ( ctrl.sawtooth_dn_effect_id < 0 )
	{
		std::cerr << "Error creating haptic effect: " << SDL_GetError() << std::endl;
	}

	SDL_HapticRunEffect(ctrl.haptic, ctrl.sawtooth_dn_effect_id, 1);
	std::cout << "Starting Sawtooth Down on joystick " << index << std::endl;
	std::cout << "   magnitude: " << ctrl.sawtooth_dn_effect.periodic.magnitude << std::endl;
	std::cout << "   period: " << ctrl.sawtooth_dn_effect.periodic.period << std::endl;
}

void Controllers::updateSawtoothDn(unsigned int index, double period, double magnitude)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];

	ctrl.sawtooth_dn_effect.periodic.period = static_cast<int>(period * 1000); // Scale to milliseconds
	ctrl.sawtooth_dn_effect.periodic.magnitude = static_cast<int>(magnitude * 32767); // Scale to 16-bit signed integer
}

void Controllers::stopSawtoothDn(unsigned int index)
{
	if ( index >= _controllers.size() )
	{
		std::cerr << "Invalid joystick index: " << index << std::endl;
		return;
	}
	Controller& ctrl = _controllers[index];
	if ( ctrl.haptic == nullptr )
	{
		std::cerr << "Haptic device not available for joystick " << index << std::endl;
		return;
	}
	if ( ctrl.sawtooth_dn_effect_id < 0 )
	{
		std::cout << "Stopping Sawtooth Down on joystick " << index << " failed" << std::endl;
		return;
	}

	SDL_HapticStopEffect(ctrl.haptic, ctrl.sawtooth_dn_effect_id);
	SDL_HapticDestroyEffect(ctrl.haptic, ctrl.sawtooth_dn_effect_id);
	ctrl.sawtooth_dn_effect_id = -1;
	std::cout << "Stopping Sawtooth Down on joystick " << index << std::endl;
}

int Controllers::initConstantEffect(SDL_Haptic* haptic, SDL_HapticEffect* effect)
{
	SDL_memset(effect, 0, sizeof(SDL_HapticEffect));
	effect->type = SDL_HAPTIC_CONSTANT;
    effect->constant.type = SDL_HAPTIC_CONSTANT;
    effect->constant.direction.type = SDL_HAPTIC_CARTESIAN;
	effect->constant.direction.dir[0] = 1; // Direction is not used for constant effect
	effect->constant.direction.dir[1] = 0; // Direction is not used for constant effect
	effect->constant.direction.dir[2] = 0; // Direction is not used for constant effect
    effect->constant.length = 0; // 5 seconds long
    effect->constant.delay = 0; // No delay
    effect->constant.button = 0; // No button
    effect->constant.interval = 0; // No interval
    effect->constant.level = 0;
    effect->constant.attack_length = 0; // No attack
    effect->constant.attack_level = 0; // No attack level
    effect->constant.fade_length = 0; // No fade
    effect->constant.fade_level = 0; // No fade level
	int result = SDL_HapticNewEffect(haptic, effect);
	if ( result < 0 )
	{
		std::cerr << "Error creating haptic effect: " << SDL_GetError() << std::endl;
	}
	return result;
}

void Controllers::initPeriodicEffect(SDL_HapticEffect* effect, uint16_t type)
{
	SDL_memset(effect, 0, sizeof(SDL_HapticEffect));
	effect->type = SDL_HAPTIC_SINE;
    /* Header */
    effect->periodic.type = type;
	effect->periodic.direction.type = SDL_HAPTIC_POLAR;
	effect->periodic.direction.dir[0] = 18000; // Direction is not used for constant effect
	effect->periodic.direction.dir[1] = 0; // Direction is not used for constant effect
	effect->periodic.direction.dir[2] = 0; // Direction is not used for constant effect
    effect->periodic.length = 0; // 5 seconds long
    effect->periodic.delay = 0; // No delay
    effect->periodic.button = 0; // No button
    effect->periodic.interval = 0; // No interval
    effect->periodic.period = 0; // Period of the wave
    effect->periodic.magnitude = 0; // Peak value
    effect->periodic.offset = 0; // Mean value of the wave
    effect->periodic.phase = 0; // Positive phase shift given by hundredth of a degree
    effect->periodic.attack_length = 0; // Duration of the attack
    effect->periodic.attack_level = 0; // Level at the start of the attack
    effect->periodic.fade_length = 0; // Duration of the fade
    effect->periodic.fade_level = 0; // Level at the end of the fade
}
