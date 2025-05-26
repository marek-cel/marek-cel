#include <Controllers.h>

#include <iostream>

#include <string>
#include <windows.h>
#include <xinput.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>

void Controllers::init()
{

    for ( uint32_t i = 0; i < kMaxJoysticks && i < XUSER_MAX_COUNT; ++i )
    {
        Controller controller;
        controller.index = i;

        XINPUT_CAPABILITIES capabilities;
        if ( ERROR_SUCCESS != XInputGetCapabilities(i, 0, &capabilities) )
        {
            std::cerr << "Failed to get capabilities for controller " << i << std::endl;
            continue;
        }

        controller.is_gamepad = capabilities.Type == XINPUT_DEVTYPE_GAMEPAD;
        controller.has_force_feedback = capabilities.Flags & XINPUT_CAPS_FFB_SUPPORTED;
        if ( controller.has_force_feedback )
        {
            std::cout << "Controller " << i << " supports force feedback." << std::endl;
        }
        else
        {
            std::cout << "Controller " << i << " does not support force feedback." << std::endl;
        }

        if ( !controller.is_gamepad )
        {
            std::cerr << "Controller " << i << " is not a gamepad." << std::endl;
            continue;
        }


        controller.axes_count = 6; // Typical gamepad has 2 thumbsticks and 2 triggers
        controller.buttons_count = 14; // Typical gamepad has 14 buttons
        _controllers.push_back(controller);
    }
}

void Controllers::update()
{
    for ( auto& controller : _controllers )
    {
        if ( controller.index >= XUSER_MAX_COUNT )
        {
            std::cerr << "Invalid controller index: " << controller.index << std::endl;
            continue;
        }

        XINPUT_STATE state;
        if ( ERROR_SUCCESS != XInputGetState(controller.index, &state) )
        {
            std::cerr << "Failed to get state for controller " << controller.index << std::endl;
            continue;
        }

        // // Axes
        controller.axes[0] = (double)state.Gamepad.sThumbLX / kAxisRange;
        controller.axes[1] = (double)state.Gamepad.sThumbLY / kAxisRange;
        controller.axes[2] = (double)state.Gamepad.sThumbRX / kAxisRange;
        controller.axes[3] = (double)state.Gamepad.sThumbRY / kAxisRange;
        controller.axes[4] = (double)state.Gamepad.bLeftTrigger / 255.0;
        controller.axes[5] = (double)state.Gamepad.bRightTrigger / 255.0;

        // // Buttons
        controller.buttons[0]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) ? 1.0 : 0.0;
        controller.buttons[1]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) ? 1.0 : 0.0;
        controller.buttons[2]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) ? 1.0 : 0.0;
        controller.buttons[3]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) ? 1.0 : 0.0;
        controller.buttons[4]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? 1.0 : 0.0;
        controller.buttons[5]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1.0 : 0.0;
        controller.buttons[6]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? 1.0 : 0.0;
        controller.buttons[7]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) ? 1.0 : 0.0;
        controller.buttons[8]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? 1.0 : 0.0;
        controller.buttons[9]  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? 1.0 : 0.0;
        controller.buttons[10] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? 1.0 : 0.0;
        controller.buttons[11] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? 1.0 : 0.0;
        controller.buttons[12] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? 1.0 : 0.0;
        controller.buttons[13] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? 1.0 : 0.0;
    }
}

