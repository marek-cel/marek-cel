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

        SDL_Haptic* haptic = nullptr; ///< Pointer to the SDL haptic device

        bool has_constant_effect = false;
        SDL_HapticEffect constant_effect;
        int constant_effect_id = -1;


        bool has_sine_wave_effect = false;
        SDL_HapticEffect sine_wave_effect;
        int sine_wave_effect_id = -1;

        bool has_left_right_effect = false;
        SDL_HapticEffect left_right_effect;
        int left_right_effect_id = -1;

        bool has_triangle_wave_effect = false;
        SDL_HapticEffect triangle_wave_effect;
        int triangle_wave_effect_id = -1;

        bool has_sawtooth_up_effect = false;
        SDL_HapticEffect sawtooth_up_effect;
        int sawtooth_up_effect_id = -1;

        bool has_sawtooth_dn_effect = false;
        SDL_HapticEffect sawtooth_dn_effect;
        int sawtooth_dn_effect_id = -1;

        bool has_periodic_effect = false;

        bool has_ramp_effect = false;
        SDL_HapticEffect ramp_effect;
        int ramp_effect_id = -1;

        bool has_springs_effect = false;
        SDL_HapticEffect springs_effect;
        int springs_effect_id = -1;

        bool has_dampers_effect = false;
        SDL_HapticEffect dampers_effect;
        int dampers_effect_id = -1;

        bool has_inertia_effect = false;
        SDL_HapticEffect inertia_effect;
        int inertia_effect_id = -1;

        bool has_friction_effect = false;
        SDL_HapticEffect friction_effect;
        int friction_effect_id = -1;
    };

    void init();
    void update();

    std::vector<Controller> getControllers() const
    {
        return _controllers;
    }

    void stopAllEffects();

    void startConstantForce(unsigned int index);
    void updateConstantForce(unsigned int index, double force_x, double force_y);
    void stopConstantForce(unsigned int index);

    void startSineWave(unsigned int index);
    void updateSineWave(unsigned int index, double period, double magnitude);
    void stopSineWave(unsigned int index);

    void startLeftRight(unsigned int index);
    void updateLeftRight(unsigned int index, double period, double magnitude);
    void stopLeftRight(unsigned int index);

    void startTriangularWave(unsigned int index);
    void updateTriangularWave(unsigned int index, double period, double magnitude);
    void stopTriangularWave(unsigned int index);

    void startSawtoothUp(unsigned int index);
    void updateSawtoothUp(unsigned int index, double period, double magnitude);
    void stopSawtoothUp(unsigned int index);

    void startSawtoothDn(unsigned int index);
    void updateSawtoothDn(unsigned int index, double period, double magnitude);
    void stopSawtoothDn(unsigned int index);

private:

    //std::vector<SDL_Joystick*> _joysticks;
    std::vector<Controller> _controllers;

    int initConstantEffect(SDL_Haptic* haptic, SDL_HapticEffect* effect);
    void initPeriodicEffect(SDL_HapticEffect* effect, uint16_t type);

};

#endif // CONTROLLERS_H