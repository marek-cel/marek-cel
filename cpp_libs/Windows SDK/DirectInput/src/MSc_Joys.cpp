#ifndef _MSC_JOYS_CPP_
#define _MSC_JOYS_CPP_
#endif

#include <cmath>

#include <algorithm>
#include <iostream>

#include <MSc_Joys.h>


const double deg2rad  = M_PI/180.0;

namespace MSc_Util
{
    int                  iJoysCount = 0;                        ///<

    MSc_JoyData          Data[MSC_MAX_JOYS_COUNT];              ///<

#   ifdef _LINUX_
    int                  iJoysFD[MSC_MAX_JOYS_COUNT] = { 0 };   ///<
    js_event             JoyEvent;                              ///<
#   endif

#   ifdef WIN32
    LPDIRECTINPUT8       pDI;                                   ///<

    LPDIRECTINPUTDEVICE8 pJoysDI[MSC_MAX_JOYS_COUNT] = { 0 };   ///<

    LPDIRECTINPUTEFFECT  pForceX[MSC_MAX_JOYS_COUNT] = { 0 };   ///<
    LPDIRECTINPUTEFFECT  pForceY[MSC_MAX_JOYS_COUNT] = { 0 };   ///<
#   endif
}

using namespace MSc_Util;

double Range( double _min, double _max, double value )
{
    double result = value;

    result = max( _min, result );
    result = min( _max, result );

    return result;
}

double Sign( double x )
{
    if ( x  < 0 ) return -1.0;
    if ( x  > 0 ) return  1.0;

    return 0.0;
}

double SignRamp( double x, double a )
{
    if ( -fabs( a ) < x && x < fabs( a ) )
    {
        return Sign( x ) * fabs( x / a );
    }
    else
    {
        return Sign( x );
    }
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS                                                           //
////////////////////////////////////////////////////////////////////////////////

MSc_Joys::MSc_Joys( void *pWinID )
{
#   ifdef WIN32
    WinID = *( (HWND*)pWinID );
#   endif

    for ( int i = 0; i < MSC_MAX_JOYS_COUNT; i++ )
    {
        memset( &(Data[i]), 0, sizeof(MSc_JoyData) );

#       ifdef _LINUX_
        iJoysFD[i] = 0;
#       endif

#       ifdef WIN32
		pJoysDI[i] = 0;
        pForceX[i] = pForceY[i] = 0;
        memset( &(Forces[i]), 0, sizeof(MSc_JoyForce) );
#       endif
    }

    resetForces();

    init();
}

////////////////////////////////////////////////////////////////////////////////

MSc_Joys::~MSc_Joys( void )
{
    clean();
}

////////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_
void MSc_Joys::startForces( void )
{
    resetForces();
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::startForces( void )
{
    resetForces();

    for ( int i = 0; i < MSC_MAX_JOYS_COUNT; i++ )
    {
        if ( pForceX[i] ) pForceX[i]->Start( 1, 0 );
        if ( pForceY[i] ) pForceY[i]->Start( 1, 0 );
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_
void MSc_Joys::stopForces( void )
{
    resetForces();

    for ( int i = 0; i < MSC_MAX_JOYS_COUNT; i++ )
    {
        updateForces( i );
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::stopForces( void )
{
    resetForces();

    for ( int i = 0; i < MSC_MAX_JOYS_COUNT; i++ )
    {
        updateForces( i );

        if ( pForceX[i] ) pForceX[i]->Stop();
        if ( pForceY[i] ) pForceY[i]->Stop();
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_
void MSc_Joys::update( void )
{
    for( int i = 0; i < iJoysCount && i < MSC_MAX_JOYS_COUNT; i++ )
    {
        while( read( iJoysFD[i], &JoyEvent, sizeof(js_event) ) > 0 )
        {
            // buttons
            if ( JoyEvent.type == JS_EVENT_BUTTON )
            {
                if ( JoyEvent.number < MSC_MAX_BUTT_COUNT ) Data[i].iButt[JoyEvent.number] = ( JoyEvent.value ) ? 1 : 0;
            }

            // axes
            if ( JoyEvent.type == JS_EVENT_AXIS )
            {
                if ( JoyEvent.number < MSC_MAX_AXIS_COUNT ) Data[i].dAxis[JoyEvent.number] = JoyEvent.value / (double)MSC_AXIS_RANGE;
            }
        }
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::update( void )
{
    HRESULT    hResult;
    DIJOYSTATE JoyState;

    for( int i = 0; i < iJoysCount && i < MSC_MAX_JOYS_COUNT; i++ )
    {
        // ---
        hResult = pJoysDI[i]->Poll();

        if ( FAILED( hResult ) )
        {
            hResult = pJoysDI[i]->Acquire();

            while ( hResult == DIERR_INPUTLOST )
            {
                hResult = pJoysDI[i]->Acquire();
            }
/*
            // If we encounter a fatal error, return failure.
            if ( ( hResult == DIERR_INVALIDPARAM ) || ( hResult == DIERR_NOTINITIALIZED ) )
            {
                return E_FAIL;
            }

            // If another application has control of this device, return successfully.
            // We'll just have to wait our turn to use the joystick.
            if ( hResult == DIERR_OTHERAPPHASPRIO ) {
                return S_OK;
            }
*/
            return; // ??? czy aby na pewno ???
        }

        // ---
        hResult = pJoysDI[i]->GetDeviceState( sizeof( DIJOYSTATE ), &JoyState );

        if( FAILED( hResult ) )
        {
            return; // The device should have been acquired during the Poll()
        }

        // Axes
        Data[i].dAxis[MSC_JOY_AXES_X]  = (double)JoyState.lX  / MSC_AXIS_RANGE;
        Data[i].dAxis[MSC_JOY_AXES_Y]  = (double)JoyState.lY  / MSC_AXIS_RANGE;
        Data[i].dAxis[MSC_JOY_AXES_Z]  = (double)JoyState.lZ  / MSC_AXIS_RANGE;

        // Rotations
        Data[i].dAxis[MSC_JOY_AXES_RX] = (double)JoyState.lRx / MSC_AXIS_RANGE;
        Data[i].dAxis[MSC_JOY_AXES_RY] = (double)JoyState.lRy / MSC_AXIS_RANGE;
        Data[i].dAxis[MSC_JOY_AXES_RZ] = (double)JoyState.lRz / MSC_AXIS_RANGE;

        // Sliders
        Data[i].dAxis[MSC_JOY_AXES_S1] = (double)JoyState.rglSlider[0] / MSC_AXIS_RANGE;
        Data[i].dAxis[MSC_JOY_AXES_S2] = (double)JoyState.rglSlider[1] / MSC_AXIS_RANGE;

        // POVs
        for ( int p_iter = 0; p_iter < 4; p_iter++ )
        {
            int iHorIndex = MSC_JOY_AXES_P1 + 2*p_iter;
            int iVerIndex = MSC_JOY_AXES_P2 + 2*p_iter;

            if ( JoyState.rgdwPOV[p_iter] == -1 )
            {
                Data[i].dAxis[iHorIndex] = 0.0;
                Data[i].dAxis[iVerIndex] = 0.0;
            }
            else
            {
                double dA_deg = (double)JoyState.rgdwPOV[p_iter] / (double)DI_DEGREES;
                double dA_rad = deg2rad * dA_deg;

                Data[i].dAxis[iHorIndex] = SignRamp( sin( dA_rad ), 0.01 );
                Data[i].dAxis[iVerIndex] = SignRamp( cos( dA_rad ), 0.01 );
            }
        }

        // Buttons
		for ( int b_iter = 0; b_iter < MSC_MAX_BUTT_COUNT; b_iter++ )
		{
			Data[i].iButt[b_iter] = ( JoyState.rgbButtons[b_iter] & 0x80 ) >> 7;
		}

        // Force Feedback
        if ( Data[i].iForce ) updateForces( i );
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////
// ACCESSORS                                                                  //
////////////////////////////////////////////////////////////////////////////////

int MSc_Joys::getJoyCount( void )
{
    return iJoysCount;
}

////////////////////////////////////////////////////////////////////////////////

int MSc_Joys::getJoyData( int iJoyNum, MSc_JoyData &JoyData )
{
    if ( iJoyNum < MSC_MAX_JOYS_COUNT )
    {
        JoyData = Data[iJoyNum];
        return 1;
    }
    else
    {
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
// MUTATORS                                                                   //
////////////////////////////////////////////////////////////////////////////////

void MSc_Joys::setForceX( int iJoyNum, double dForceNorm )
{
    if ( iJoyNum < MSC_MAX_JOYS_COUNT ) Forces[iJoyNum].dForceX = - Range( -1.0, 1.0, dForceNorm );
}

////////////////////////////////////////////////////////////////////////////////

void MSc_Joys::setForceY( int iJoyNum, double dForceNorm )
{
    if ( iJoyNum < MSC_MAX_JOYS_COUNT ) Forces[iJoyNum].dForceY = - Range( -1.0, 1.0, dForceNorm );
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS                                                          //
////////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_
void MSc_Joys::clean( void ) {}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::clean( void )
{
    for ( int i = 0; i < iJoysCount && i < MSC_MAX_JOYS_COUNT; i++ )
    {
        if ( pJoysDI[i] ) pJoysDI[i]->Unacquire();
        if ( pJoysDI[i] ) pJoysDI[i]->Release();
    }

    pDI->Release();
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_
void MSc_Joys::init( void )
{
    for ( int i = 0; i < MSC_MAX_JOYS_COUNT; i++ )
    {
        char acTmpDev[255];

        sprintf ( acTmpDev, "/dev/input/js%d", i );

        iJoysFD[i] = open( acTmpDev, O_NONBLOCK );

        if ( iJoysFD[i] > 0 )
        {
            Data[i].iActive = 1;

            char cTmpCount;

            ioctl( iJoysFD[i], JSIOCGAXES,     &cTmpCount     );  Data[i].iAxisCount = min( (int)cTmpCount, MSC_MAX_AXIS_COUNT );
            ioctl( iJoysFD[i], JSIOCGBUTTONS,  &cTmpCount     );  Data[i].iButtCount = min( (int)cTmpCount, MSC_MAX_BUTT_COUNT );
            ioctl( iJoysFD[i], JSIOCGNAME(64), Data[i].acName );

            iJoysCount++;
        }
        else
        {
            break; // ??? czy napewno ??? (chyba tak)
        }
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::init( void )
{
    if (
         FAILED( DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDI, NULL ) )
       )
    {
        std::cerr << "[  ERROR  ] MSc_Joys: Creating DirectInput failed." << std::endl;
        return;
    }

    // enuming joysticks
    if (
         FAILED( pDI->EnumDevices( DI8DEVCLASS_GAMECTRL, enumJoysCallback, NULL, DIEDFL_ATTACHEDONLY ) )
       )
    {
        std::cerr << "[  ERROR  ] MSc_Joys: Enumerating devices failed." << std::endl;
        return;
    }

    // for every enumerated joys
    for( int i = 0; i < iJoysCount && i < MSC_MAX_JOYS_COUNT; i++ )
    {
        // ---
        DIDEVICEINSTANCE DevInst;
        DevInst.dwSize = sizeof( DIDEVICEINSTANCE );

        if (
             FAILED( pJoysDI[i]->GetDeviceInfo( &DevInst ) )
           )
        {
            std::cerr << "[  ERROR  ] MSc_Joys: Getting #" << i << " device info failed." << std::endl;
        }
        else
        {
            strncpy_s( Data[i].acName, sizeof(Data[i].acName), DevInst.tszProductName, _TRUNCATE );
        }

        // ---
        if (
             FAILED( pJoysDI[i]->SetDataFormat( &c_dfDIJoystick ) )
           )
        {
            std::cerr << "[  ERROR  ] MSc_Joys: Setting data format of " << Data[i].acName << " failed." << std::endl;
            return;
        }

        // ---
        if (
             FAILED( pJoysDI[i]->SetCooperativeLevel( WinID, DISCL_EXCLUSIVE | DISCL_BACKGROUND ) )
           )
        {
			std::cerr << "[  ERROR  ] MSc_Joys: Setting cooperation level of " << Data[i].acName << " failed." << std::endl;
            return;
        }

        // ---
        DIDEVCAPS Caps;
        Caps.dwSize = sizeof( DIDEVCAPS );
        if (
             FAILED( pJoysDI[i]->GetCapabilities( &Caps ) )
           )
        {
            std::cerr << "[  ERROR  ] MSc_Joys: Setting getting capabilities of " << Data[i].acName << " failed." << std::endl;
            return;
        }
        else
        {
            Data[i].iAxisCount = Caps.dwAxes;
            Data[i].iButtCount = Caps.dwButtons;
            Data[i].iForce     = ( Caps.dwFlags & DIDC_FORCEFEEDBACK ) ? 1 : 0;

            if ( Data[i].iForce )
            {
                std::cout << "---         MSc_Joys: " << Data[i].acName << " is Force Feedback capable device. " << std::endl;
            }
            else
            {
                std::cout << "---         MSc_Joys: " << Data[i].acName << " is NOT Force Feedback capable device. " << std::endl;
            }
        }

        // ---
        if (
             FAILED( pJoysDI[i]->EnumObjects( enumAxesCallback, pJoysDI[i], DIDFT_AXIS ) )
           )
        {
            return;
        }

        Data[i].iActive = 1;

        if ( Data[i].iForce ) initForces( i );
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::initForces( int iJoyNum )
{
    initForceX( iJoyNum );
    initForceY( iJoyNum );
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::initForceX( int iJoyNum )
{
    // see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx

    DWORD Axes   = DIJOFS_X;
    LONG  Direct = 1;

    DICONSTANTFORCE ConstForce;
    DIEFFECT        Effect;

    //-----------------------------------------------------------------//

    ConstForce.lMagnitude = 0;

    //-----------------------------------------------------------------//

    Effect.dwSize                  = sizeof( DIEFFECT );
    Effect.dwFlags                 = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    Effect.dwDuration              = INFINITE;
    Effect.dwSamplePeriod          = 0;
    Effect.dwGain                  = DI_FFNOMINALMAX;
    Effect.dwTriggerButton         = DIEB_NOTRIGGER;
    Effect.dwTriggerRepeatInterval = 0;
    Effect.cAxes                   = 1;
    Effect.rgdwAxes                = &Axes;
    Effect.rglDirection            = &Direct;
    Effect.lpEnvelope              = NULL;
    Effect.cbTypeSpecificParams    = sizeof( DICONSTANTFORCE );
    Effect.lpvTypeSpecificParams   = &ConstForce;
    Effect.dwStartDelay            = 0;

    if (
         FAILED( pJoysDI[iJoyNum]->CreateEffect( GUID_ConstantForce, &Effect, &(pForceX[iJoyNum]), NULL ) )
       )
    {
		std::cerr << "[  ERROR  ] MSc_Joys: Creating of constant force effect (X-axis) failed." << std::endl;
        pForceX[iJoyNum] = 0;
    }

    pForceX[iJoyNum]->Stop();
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::initForceY( int iJoyNum )
{
    // see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx

    DWORD Axes   = DIJOFS_Y;
    LONG  Direct = 1;

    DICONSTANTFORCE ConstForce;
    DIEFFECT        Effect;

    //-----------------------------------------------------------------//

    ConstForce.lMagnitude = 0;

    //-----------------------------------------------------------------//

    Effect.dwSize                  = sizeof( DIEFFECT );
    Effect.dwFlags                 = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
    Effect.dwDuration              = INFINITE;
    Effect.dwSamplePeriod          = 0;
    Effect.dwGain                  = DI_FFNOMINALMAX;
    Effect.dwTriggerButton         = DIEB_NOTRIGGER;
    Effect.dwTriggerRepeatInterval = 0;
    Effect.cAxes                   = 1;
    Effect.rgdwAxes                = &Axes;
    Effect.rglDirection            = &Direct;
    Effect.lpEnvelope              = NULL;
    Effect.cbTypeSpecificParams    = sizeof( DICONSTANTFORCE );
    Effect.lpvTypeSpecificParams   = &ConstForce;
    Effect.dwStartDelay            = 0;

    if (
         FAILED( pJoysDI[iJoyNum]->CreateEffect( GUID_ConstantForce, &Effect, &(pForceY[iJoyNum]), NULL ) )
       )
    {
		std::cerr << "[  ERROR  ] MSc_Joys: Creating of constant force effect (Y-axis) failed." << std::endl;
        pForceY[iJoyNum] = 0;
    }

    pForceY[iJoyNum]->Stop();
}
#endif

////////////////////////////////////////////////////////////////////////////////

void MSc_Joys::resetForces( void )
{
    for ( int i = 0; i < MSC_MAX_JOYS_COUNT; i++ )
    {
        Forces[i].dForceX = 0.0;
        Forces[i].dForceY = 0.0;
    }
}

////////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_
void MSc_Joys::updateForces( int iJoyNum ) {}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::updateForces( int iJoyNum )
{
    updateForceX( iJoyNum );
    updateForceY( iJoyNum );
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::updateForceX( int iJoyNum )
{
    // see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx

    if ( pForceX[iJoyNum] )
    {
        //DWORD Axes[2]   = { DIJOFS_X, DIJOFS_Y };
        //LONG  Direct[2] = { 1, 0 };

        DWORD Axes   = DIJOFS_X;
        LONG  Direct = 1;

        DICONSTANTFORCE ConstForce;
        DIEFFECT        Effect;

        //-----------------------------------------------------------------//

        ConstForce.lMagnitude = (long)( Forces[iJoyNum].dForceX * (double)DI_FFNOMINALMAX );

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
        //        std::cerr << "[  ERROR  ] MSc_Joys: Setting parameters of constant force effect (X-axis) failed." << std::endl;
        //    }
        //}
        //else
        //{
        //    std::cerr << "[  ERROR  ] MSc_Joys: Getting parameters of constant force effect (X-axis) failed." << std::endl;
        //}

        Effect.dwSize                  = sizeof( DIEFFECT );
        Effect.dwFlags                 = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
        Effect.dwDuration              = INFINITE;
        Effect.dwSamplePeriod          = 0;
        Effect.dwGain                  = DI_FFNOMINALMAX;
        Effect.dwTriggerButton         = DIEB_NOTRIGGER;
        Effect.dwTriggerRepeatInterval = 0;
        //Effect.cAxes                   = 2;
        //Effect.rgdwAxes                = Axes;
        //Effect.rglDirection            = Direct;
        Effect.cAxes                   = 1;
        Effect.rgdwAxes                = &Axes;
        Effect.rglDirection            = &Direct;
        Effect.lpEnvelope              = NULL;
        Effect.cbTypeSpecificParams    = sizeof( DICONSTANTFORCE );
        Effect.lpvTypeSpecificParams   = &ConstForce;
        Effect.dwStartDelay            = 0;

        pForceX[iJoyNum]->SetParameters( &Effect, DIEP_TYPESPECIFICPARAMS | DIEP_START );
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void MSc_Joys::updateForceY( int iJoyNum )
{
    // see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx

    if ( pForceY[iJoyNum] )
    {
        //DWORD Axes[2]   = { DIJOFS_X, DIJOFS_Y };
        //LONG  Direct[2] = { 0, 1 };

        DWORD Axes   = DIJOFS_Y;
        LONG  Direct = 1;

        DICONSTANTFORCE ConstForce;
        DIEFFECT        Effect;

        //-----------------------------------------------------------------//

        ConstForce.lMagnitude = (long)( Forces[iJoyNum].dForceY * (double)DI_FFNOMINALMAX );

        //-----------------------------------------------------------------//

        //if (
        //     SUCCEEDED( pForceY[iJoyNum]->GetParameters( &Effect, DIEP_ALLPARAMS ) )
        //   )
        //{
        //    Effect.cbTypeSpecificParams    = sizeof( DICONSTANTFORCE );
        //    Effect.lpvTypeSpecificParams   = &ConstForce;
        //
        //    if (
        //         FAILED( pForceY[iJoyNum]->SetParameters( &Effect, DIEP_TYPESPECIFICPARAMS | DIEP_START ) )
        //       )
        //    {
        //        std::cerr << "[  ERROR  ] MSc_Joys: Setting parameters of constant force effect (Y-axis) failed." << std::endl;
        //    }
        //}
        //else
        //{
        //    std::cerr << "[  ERROR  ] MSc_Joys: Getting parameters of constant force effect (Y-axis) failed." << std::endl;
        //}

        Effect.dwSize                  = sizeof( DIEFFECT );
        Effect.dwFlags                 = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
        Effect.dwDuration              = INFINITE;
        Effect.dwSamplePeriod          = 0;
        Effect.dwGain                  = DI_FFNOMINALMAX;
        Effect.dwTriggerButton         = DIEB_NOTRIGGER;
        Effect.dwTriggerRepeatInterval = 0;
        //Effect.cAxes                   = 2;
        //Effect.rgdwAxes                = Axes;
        //Effect.rglDirection            = Direct;
        Effect.cAxes                   = 1;
        Effect.rgdwAxes                = &Axes;
        Effect.rglDirection            = &Direct;
        Effect.lpEnvelope              = NULL;
        Effect.cbTypeSpecificParams    = sizeof( DICONSTANTFORCE );
        Effect.lpvTypeSpecificParams   = &ConstForce;
        Effect.dwStartDelay            = 0;

        pForceY[iJoyNum]->SetParameters( &Effect, DIEP_TYPESPECIFICPARAMS | DIEP_START );
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////
// DIRECT INPUT CALLBACKS                                                     //
////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32

BOOL CALLBACK enumJoysCallback( const DIDEVICEINSTANCE* pDevInst, VOID* pContext )
{
    HRESULT hResult;

    LPDIRECTINPUTDEVICE8 pJoy;

    // Obtain an interface to the enumerated joystick.
    hResult = pDI->CreateDevice( pDevInst->guidInstance, &pJoy, NULL );

    if ( SUCCEEDED( hResult ) && iJoysCount < MSC_MAX_JOYS_COUNT )
    {
        pJoysDI[iJoysCount] = pJoy;
        iJoysCount++;
    }

    if ( iJoysCount < MSC_MAX_JOYS_COUNT )
    {
        return DIENUM_CONTINUE;
    }
    else
    {
        return DIENUM_STOP;
    }
}

////////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK enumAxesCallback( const DIDEVICEOBJECTINSTANCE* pDevObjInst, VOID* pContext )
{
    LPDIRECTINPUTDEVICE8 pJoy = (LPDIRECTINPUTDEVICE8)pContext;

    DIPROPRANGE DI_PropRange;

    DI_PropRange.diph.dwSize       = sizeof( DIPROPRANGE );
    DI_PropRange.diph.dwHeaderSize = sizeof( DIPROPHEADER );
    DI_PropRange.diph.dwObj        = pDevObjInst->dwType; // Specify the enumerated axis
    DI_PropRange.diph.dwHow        = DIPH_BYID;
    DI_PropRange.lMin              = - MSC_AXIS_RANGE;
    DI_PropRange.lMax              =   MSC_AXIS_RANGE;

    // Set the range for the axis
    if (
         FAILED( pJoy->SetProperty( DIPROP_RANGE, &DI_PropRange.diph ) )
       )
    {
        return DIENUM_STOP;
    }

    return DIENUM_CONTINUE;
}

#endif

////////////////////////////////////////////////////////////////////////////////
// END OF FILE                                                                //
////////////////////////////////////////////////////////////////////////////////
