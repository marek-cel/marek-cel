#ifndef JOYSTICKS_H
#define JOYSTICKS_H

#include <string>
#include <vector>

#include <SDL.h>

class Joysticks
{
public:

    struct Joystick
    {
        std::string name;
        int id;
        uint8_t num_axes = 0;   ///< Number of axes
        uint8_t num_buttons = 0;///< Number of buttons
        uint8_t num_hats = 0;   ///< Number of hats
    };

    void init();

private:

    //std::vector<Joystick> _joysticks;
    std::vector<SDL_Joystick*> _joysticks;

};

#endif // JOYSTICKS_H