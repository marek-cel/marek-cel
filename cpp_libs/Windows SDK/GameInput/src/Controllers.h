#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <string>
#include <vector>

#include <windows.h>
#include <GameInput.h>
#include <Xinput.h>

class Controllers
{
public:

    static constexpr int kMaxAxes = 16;
    static constexpr int kMaxButtons = 32;
    static constexpr int kMaxJoysticks = 8;
    static constexpr double kAxisRange = 32767.0;

    struct Controller
    {
        uint32_t index = 0;

        std::string name;
        uint8_t axes_count = 0;
        uint8_t buttons_count = 0;

        bool is_gamepad = false;

        bool has_force_feedback = false;

        double axes[kMaxAxes] = {0};
        double buttons[kMaxButtons] = {0};
    };

    std::vector<Controller> getControllers() const { return _controllers; }

    void init();
    void update();

private:

    IGameInput* _gameInput = nullptr;

    std::vector<Controller> _controllers;
};

#endif // CONTROLLERS_H