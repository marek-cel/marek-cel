#include <Controllers.h>

#include <iostream>

void Controllers::init()
{
    HRESULT hr = GameInputCreate(&_gameInput);
    if ( FAILED(hr) )
    {
        std::cerr << "Failed to create GameInput interface. HRESULT: 0x" << std::hex << hr << std::endl;
        throw std::runtime_error("Failed to create GameInput interface.");
    }

    hr = _gameInput->RegisterDeviceCallback(
            nullptr,                    // All devices
            GameInputKindGamepad,       // Only gamepads
            GameInputDeviceConnected,   // Connection events
            GameInputBlockingEnumeration, // Wait for initial enumeration
            this,                       // Context
            DeviceCallback,            // Callback function
            &_callbackToken);
}

void Controllers::update()
{

}

