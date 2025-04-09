#include <Joystick.h>

#include <iostream>

BOOL CALLBACK enumJoysCallback(const DIDEVICEINSTANCE* dev_inst, VOID* context);
BOOL CALLBACK enumAxesCallback(const DIDEVICEOBJECTINSTANCE* dev_obj_inst, VOID* context);

Joystick::Data Joystick::_data;

void Joystick::init(HWND winID)
{
    _winID = winID;

    if ( FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&_data.di, NULL)) )
    {
        std::cerr << "Creating DirectInput failed." << std::endl;
        exit(-1);
    }

    if ( FAILED(_data.di->EnumDevices(DI8DEVCLASS_GAMECTRL, static_cast<LPDIENUMDEVICESCALLBACK>(enumJoysCallback), NULL, DIEDFL_ATTACHEDONLY)) )
    {
        std::cerr << "Enumerating devices failed." << std::endl;
        exit(-1);
    }

    for (auto& joy_data : _data.joys)
    {
        std::cout << "Initializing joystick" << std::endl;
        LPDIRECTINPUTDEVICE8 dev = joy_data.dev;

        DIDEVICEINSTANCE dev_inst;
        DIDEVCAPS dev_caps;

        dev_inst.dwSize = sizeof(DIDEVICEINSTANCE);
        dev_caps.dwSize = sizeof(DIDEVCAPS);

        if ( FAILED(dev->GetDeviceInfo(&dev_inst)) )
        {
            std::cerr << "Getting device info failed." << std::endl;
            exit(-1);
        }
        else
        {
            joy_data.name = dev_inst.tszProductName;
            std::cout << "Joystick name: " << joy_data.name << std::endl;
        }

        if ( FAILED(dev->SetDataFormat(&c_dfDIJoystick)) )
        {
            std::cerr << "Setting data format of " << joy_data.name << " failed." << std::endl;
            exit(-1);
        }

        if ( FAILED(dev->SetCooperativeLevel(_winID, DISCL_EXCLUSIVE | DISCL_BACKGROUND)) )
        {
            std::cerr << "Setting cooperation level of " << joy_data.name << " failed." << std::endl;
            exit(-1);
        }

        if ( FAILED(dev->GetCapabilities(&dev_caps)) )
        {
            std::cerr << "Setting getting capabilities of " << joy_data.name << " failed." << std::endl;
            exit(-1);
        }
        else
        {
            joy_data.axes_count = dev_caps.dwAxes;
            joy_data.buttons_count = dev_caps.dwButtons;
            joy_data.force_feedback = (dev_caps.dwFlags & DIDC_FORCEFEEDBACK) ? true : false;
            joy_data.is_xinput_compatible = (dev_caps.dwFlags & DIDC_ATTACHED) ? true : false;

            if ( joy_data.force_feedback )
            {
                std::cout << "Joystick " << joy_data.name << " has force feedback." << std::endl;
            }
            else
            {
                std::cout << "Joystick " << joy_data.name << " has no force feedback." << std::endl;
            }

            if ( joy_data.is_xinput_compatible )
            {
                std::cout << "Joystick " << joy_data.name << " is XInput compatible." << std::endl;
            }
            else
            {
                std::cout << "Joystick " << joy_data.name << " is not XInput compatible." << std::endl;
            }
        }

        if ( FAILED(dev->EnumObjects(enumAxesCallback, dev, DIDFT_AXIS)) )
        {
            std::cerr << "Enumerating axes of " << joy_data.name << " failed." << std::endl;
            exit(-1);
        }

        if ( joy_data.force_feedback )
        {
            initForces(joy_data);
        }
    }
}

void Joystick::update()
{
    for (auto& joy_data : _data.joys)
    {
        //std::cout << "Updating joystick" << std::endl;
        LPDIRECTINPUTDEVICE8 dev = joy_data.dev;

        HRESULT result;
        DIJOYSTATE joy_state;

        result = dev->Poll();
        if ( FAILED(result) )
        {
            result = dev->Acquire();

            while ( result == DIERR_INPUTLOST )
            {
                result = dev->Acquire();
            }

            // // If we encounter a fatal error, return failure.
            // if ( result == DIERR_INVALIDPARAM || result == DIERR_NOTINITIALIZED )
            // {
            //     return E_FAIL;
            // }

            // // If another application has control of this device, return successfully.
            // // We'll just have to wait our turn to use the joystick.
            // if ( result == DIERR_OTHERAPPHASPRIO )
            // {
            //     return S_OK;
            // }
        }

        result = dev->GetDeviceState(sizeof(DIJOYSTATE), &joy_state);

        if( FAILED(result) )
        {
            std::cerr << "Getting device state of " << joy_data.name << " failed." << std::endl;
            return;
        }

        // Axes
        joy_data.axes[0] = (double)joy_state.lX  / kAxisRange;
        joy_data.axes[1] = (double)joy_state.lY  / kAxisRange;
        joy_data.axes[2] = (double)joy_state.lZ  / kAxisRange;

        joy_data.axes[3] = (double)joy_state.lRx / kAxisRange;
        joy_data.axes[4] = (double)joy_state.lRy / kAxisRange;
        joy_data.axes[5] = (double)joy_state.lRz / kAxisRange;

        joy_data.axes[6] = (double)joy_state.rglSlider[0] / kAxisRange;
        joy_data.axes[7] = (double)joy_state.rglSlider[1] / kAxisRange;

        // Buttons
        for ( unsigned int i = 0; i < kMaxButtons; ++i )
        {
            joy_data.buttons[i] = ( joy_state.rgbButtons[i] & 0x80 ) >> 7;
        }

        // Force feedback
        if ( joy_data.force_feedback )
        {
            updateForces(joy_data);
        }
    }
}

void Joystick::startForcesX()
{
    for (auto& joy_data : _data.joys)
    {
        if ( joy_data.force_feedback )
        {
            std::cout << "Starting forces X" << std::endl;
            joy_data.magnitude_x = 0.0;
            updateForces(joy_data);
            joy_data.force_x->Start(1, 0);
        }
    }
}

void Joystick::startForcesY()
{
    for (auto& joy_data : _data.joys)
    {
        if ( joy_data.force_feedback )
        {
            std::cout << "Starting forces Y" << std::endl;
            joy_data.magnitude_y = 0.0;
            updateForces(joy_data);
            joy_data.force_y->Start(1, 0);
        }
    }
}

void Joystick::stopForcesX()
{
    for (auto& joy_data : _data.joys)
    {
        if ( joy_data.force_feedback )
        {
            std::cout << "Stopping forces X" << std::endl;
            joy_data.magnitude_x = 0.0;
            updateForces(joy_data);
            joy_data.force_x->Stop();
        }
    }
}

void Joystick::stopForcesY()
{
    for (auto& joy_data : _data.joys)
    {
        if ( joy_data.force_feedback )
        {
            std::cout << "Stopping forces Y" << std::endl;
            joy_data.magnitude_y = 0.0;
            updateForces(joy_data);
            joy_data.force_y->Stop();
        }
    }
}

void Joystick::initForces(Data::Joystick& joy_data)
{
    LPDIRECTINPUTDEVICE8 dev = joy_data.dev;
    initConstantForce(dev, DIJOFS_X, &joy_data.force_x);
    initConstantForce(dev, DIJOFS_Y, &joy_data.force_y);
}

void Joystick::initConstantForce(LPDIRECTINPUTDEVICE8 dev, DWORD axes, LPDIRECTINPUTEFFECT* force)
{
    // see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx

    LONG direct = 1;

    DICONSTANTFORCE const_force;
    DIEFFECT effect;

    const_force.lMagnitude = 0;

    effect.dwSize                  = sizeof(DIEFFECT);
    effect.dwFlags                 = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    effect.dwDuration              = INFINITE;
    effect.dwSamplePeriod          = 0;
    effect.dwGain                  = DI_FFNOMINALMAX;
    effect.dwTriggerButton         = DIEB_NOTRIGGER;
    effect.dwTriggerRepeatInterval = 0;
    effect.cAxes                   = 1;
    effect.rgdwAxes                = &axes;
    effect.rglDirection            = &direct;
    effect.lpEnvelope              = NULL;
    effect.cbTypeSpecificParams    = sizeof(DICONSTANTFORCE);
    effect.lpvTypeSpecificParams   = &const_force;
    effect.dwStartDelay            = 0;

    if ( FAILED(dev->CreateEffect(GUID_ConstantForce, &effect, force, NULL)) )
    {
		std::cerr << "Creating of constant force effect failed" << std::endl;
        exit(-1);
    }

    (*force)->Stop();
}

void Joystick::updateForces(Data::Joystick& joy_data)
{
    updateConstantForce(DIJOFS_X, &joy_data.force_x, joy_data.magnitude_x);
    updateConstantForce(DIJOFS_Y, &joy_data.force_y, joy_data.magnitude_y);
}

void Joystick::updateConstantForce(DWORD axes, LPDIRECTINPUTEFFECT* force, double magnitude)
{
    // see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx

    if ( force == nullptr )
    {
        std::cerr << "Force is null" << std::endl;
        return;
    }

    //DWORD Axes[2]   = { DIJOFS_X, DIJOFS_Y };
    //LONG  Direct[2] = { 1, 0 };

    LONG direct = 1;

    DICONSTANTFORCE const_force;
    DIEFFECT effect;

    //-----------------------------------------------------------------//

    const_force.lMagnitude = (long)(magnitude * (double)DI_FFNOMINALMAX);

    //-----------------------------------------------------------------//

    //if (
    //     SUCCEEDED( pForceX[iJoyNum]->GetParameters( &Effect, DIEP_ALLPARAMS ) )
    //   )
    //{
    //    Effect.cbTypeSpecificParams    = sizeof( DICONSTANTFORCE );
    //    Effect.lpvTypeSpecificParams   = &ConstForce;
    //
    //    if (
    //         FAILED( pForceX[iJoyNum]->SetParameters( &Effect, DIEP_TYPESPECIFICPARAMS | DIEP_START ) )
    //       )
    //    {
    //        cerr << "[  ERROR  ] MSc_Joys: Setting parameters of constant force effect (X-axis) failed." << endl;
    //    }
    //}
    //else
    //{
    //    cerr << "[  ERROR  ] MSc_Joys: Getting parameters of constant force effect (X-axis) failed." << endl;
    //}

    effect.dwSize                  = sizeof( DIEFFECT );
    effect.dwFlags                 = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    effect.dwDuration              = INFINITE;
    effect.dwSamplePeriod          = 0;
    effect.dwGain                  = DI_FFNOMINALMAX;
    effect.dwTriggerButton         = DIEB_NOTRIGGER;
    effect.dwTriggerRepeatInterval = 0;
    //Effect.cAxes                   = 2;
    //Effect.rgdwAxes                = Axes;
    //Effect.rglDirection            = Direct;
    effect.cAxes                   = 1;
    effect.rgdwAxes                = &axes;
    effect.rglDirection            = &direct;
    effect.lpEnvelope              = NULL;
    effect.cbTypeSpecificParams    = sizeof( DICONSTANTFORCE );
    effect.lpvTypeSpecificParams   = &const_force;
    effect.dwStartDelay            = 0;

    (*force)->SetParameters(&effect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
}

BOOL CALLBACK enumJoysCallback(const DIDEVICEINSTANCE* dev_inst, VOID* context)
{
    Joystick::Data* data = Joystick::getData();

    LPDIRECTINPUT8 di = data->di;
    LPDIRECTINPUTDEVICE8 joy;

    // Obtain an interface to the enumerated joystick.
    HRESULT result = di->CreateDevice(dev_inst->guidInstance, &joy, NULL );

    if ( SUCCEEDED(result) && data->joys.size() < Joystick::kMaxJoysticks )
    {
        std::cout << "Found joystick" << std::endl;
        Joystick::Data::Joystick joyData;
        joyData.dev = joy;
        data->joys.push_back(joyData);
    }

    if ( data->joys.size() < Joystick::kMaxJoysticks )
    {
        return DIENUM_CONTINUE;
    }
    else
    {
        return DIENUM_STOP;
    }
}

BOOL CALLBACK enumAxesCallback(const DIDEVICEOBJECTINSTANCE* dev_obj_inst, VOID* context)
{
    LPDIRECTINPUTDEVICE8 joy = (LPDIRECTINPUTDEVICE8)context;

    DIPROPRANGE prop_range;

    prop_range.diph.dwSize       = sizeof(DIPROPRANGE);
    prop_range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    prop_range.diph.dwObj        = dev_obj_inst->dwType; // Specify the enumerated axis
    prop_range.diph.dwHow        = DIPH_BYID;
    prop_range.lMin              = -Joystick::kAxisRange;
    prop_range.lMax              =  Joystick::kAxisRange;

    // Set the range for the axis
    if ( FAILED(joy->SetProperty(DIPROP_RANGE, &prop_range.diph)) )
    {
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}