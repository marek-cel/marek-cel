#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <string>
#include <vector>

#include <dinput.h>
#include <Xinput.h>

class Joystick
{
public:

    static constexpr int kMaxAxes = 16;
    static constexpr int kMaxButtons = 32;
    static constexpr int kMaxJoysticks = 8;
    static constexpr double kAxisRange = 32767.0;

    struct Data
    {
        LPDIRECTINPUT8 di = nullptr;

        struct Joystick
        {
            LPDIRECTINPUTDEVICE8 dev = nullptr;
            LPDIRECTINPUTEFFECT force_x = nullptr;
            LPDIRECTINPUTEFFECT force_y = nullptr;

            std::string name;
            uint8_t axes_count = 0;
            uint8_t buttons_count = 0;
            bool force_feedback = false;
            bool is_xinput_compatible = false;

            XINPUT_STATE xinput_state;

            bool has_sine_wave_effect = false;
            bool has_constant_force = false;
            bool has_ramp_force = false;

            double axes[kMaxAxes] = {0};
            double buttons[kMaxButtons] = {0};

            double magnitude_x = {0};
            double magnitude_y = {0};
        };

        std::vector<Joystick> joys;
    };

    static Data* getData() { return &_data; }

    void init(HWND winID);
    void update();

    void startForcesX();
    void startForcesY();
    void stopForcesX();
    void stopForcesY();

private:

    HWND _winID;

    static Data _data;

    void initForces(Data::Joystick& joy_data);
    void initConstantForce(LPDIRECTINPUTDEVICE8 dev, DWORD axes, LPDIRECTINPUTEFFECT* force);

    void updateDirectInput(Data::Joystick& joy_data);
    void updateXInput(int index, Data::Joystick& joy_data);

    void updateForces(Data::Joystick& joy_data);
    void updateConstantForce(DWORD axes, LPDIRECTINPUTEFFECT* force, double magnitude);
};

#endif // JOYSTICK_H