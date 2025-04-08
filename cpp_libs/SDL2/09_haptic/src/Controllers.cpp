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

			std::cout << "Initializing haptic effects..." << std::endl;
			joystick.constant_effect_id = initConstantEffects(joystick.haptic, &joystick.constant_effect);
		}
		else
		{
			std::cout << "Joystick " << i << " does not have haptic feedback." << std::endl;
		}

		_controllers.push_back(joystick);
		std::cout << "Joystick " << i << ": " << joystick.name << std::endl;
		std::cout << "  Axes: " << (int)joystick.num_axes << std::endl;
		std::cout << "  Buttons: " << (int)joystick.num_buttons << std::endl;
		std::cout << "  Hats: " << (int)joystick.num_hats << std::endl;
		std::cout << "  Vendor: " << std::hex << joystick.vendor << std::dec << std::endl;
		std::cout << "  Product: " << std::hex << joystick.product << std::dec << std::endl;
		std::cout << "  Haptic: " << (joystick.has_haptic ? "Yes" : "No") << std::endl;
		std::cout << "  Joystick ID: " << (int)joystick.id << std::endl;
		int supported_effects = SDL_HapticQuery(joystick.haptic);
		std::cout << "  Supports SDL_HAPTIC_CONSTANT: " << ((supported_effects & SDL_HAPTIC_CONSTANT) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_SINE: " << ((supported_effects & SDL_HAPTIC_SINE) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_LEFTRIGHT: " << ((supported_effects & SDL_HAPTIC_LEFTRIGHT) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_TRIANGLE: " << ((supported_effects & SDL_HAPTIC_TRIANGLE) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_SAWTOOTHUP: " << ((supported_effects & SDL_HAPTIC_SAWTOOTHUP) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_SAWTOOTHDOWN: " << ((supported_effects & SDL_HAPTIC_SAWTOOTHDOWN) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_RAMP: " << ((supported_effects & SDL_HAPTIC_RAMP) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_SPRING: " << ((supported_effects & SDL_HAPTIC_SPRING) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_DAMPER: " << ((supported_effects & SDL_HAPTIC_DAMPER) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_INERTIA: " << ((supported_effects & SDL_HAPTIC_INERTIA) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_FRICTION: " << ((supported_effects & SDL_HAPTIC_FRICTION) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_CUSTOM: " << ((supported_effects & SDL_HAPTIC_CUSTOM) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_GAIN: " << ((supported_effects & SDL_HAPTIC_GAIN) ? "Yes" : "No") << std::endl;
		std::cout << "  Supports SDL_HAPTIC_AUTOCENTER: " << ((supported_effects & SDL_HAPTIC_AUTOCENTER) ? "Yes" : "No") << std::endl;
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

void Controllers::stopAllEffects()
{
	for ( auto& controller : _controllers )
	{
		if ( controller.haptic )
		{
			SDL_HapticStopAll(controller.haptic);
		}
	}
}

void Controllers::startConstantForce(unsigned int index)
{
	if ( _controllers[index].constant_effect_id < 0 )
	{
		std::cout << "Starting Constant Force on joystick " << index << " failed" << std::endl;
		return;
	}

	SDL_HapticRunEffect(_controllers[index].haptic, _controllers[index].constant_effect_id, 1);
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

int Controllers::initConstantEffects(SDL_Haptic* haptic, SDL_HapticEffect* effect)
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