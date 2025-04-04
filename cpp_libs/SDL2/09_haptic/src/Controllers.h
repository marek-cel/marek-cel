#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <string>
#include <vector>

#include <SDL.h>

class Controllers
{
public:

    static constexpr int kMaxAxes = 16;
    static constexpr int kMaxButtons = 32;
    static constexpr int kMaxJoysticks = 8;
    static constexpr double kAxisRange = 32767.0;

    struct Controller
    {
        SDL_Joystick* joystick = nullptr; ///< Pointer to the SDL joystick
        SDL_JoystickID id;

        std::string name;
        uint8_t num_axes = 0;   ///< Number of axes
        uint8_t num_buttons = 0;///< Number of buttons
        uint8_t num_hats = 0;   ///< Number of hats
        uint16_t vendor;
        uint16_t product;
        bool has_haptic = false; ///< Whether the joystick has haptic feedback

        double axes[kMaxAxes] = {0};
        bool buttons[kMaxButtons] = {false};
    };

    void init();
    void update();

    std::vector<Controller> getControllers() const
    {
        return _controllers;
    }

private:

    //std::vector<SDL_Joystick*> _joysticks;
    std::vector<Controller> _controllers;

};

#endif // CONTROLLERS_H