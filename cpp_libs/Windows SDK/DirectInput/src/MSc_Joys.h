#ifndef _MSC_JOYS_H_
#define _MSC_JOYS_H_

////////////////////////////////////////////////////////////////////////////////
// INCLUDES                                                                   //
////////////////////////////////////////////////////////////////////////////////

// #include <MSc_Base.h>
// #include <MSc_Util.h>

#ifdef _LINUX_
    #include <linux/joystick.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <unistd.h>
#endif

#ifdef WIN32
    #include <dinput.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS                                                                //
////////////////////////////////////////////////////////////////////////////////

#define MSC_MAX_JOYS_COUNT 8
#define MSC_MAX_AXIS_COUNT 16
#define MSC_MAX_BUTT_COUNT 32

#define MSC_AXIS_RANGE 32767

////////////////////////////////////////////////////////////////////////////////

// #ifdef WIN32
//     #define DIRECTINPUT_VERSION 0x0800
// #endif

////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS                                                       //
////////////////////////////////////////////////////////////////////////////////

enum MSC_JOY_AXES
{
    MSC_JOY_AXES_X = 0,     ///<  0: X-axis deflection
    MSC_JOY_AXES_Y,         ///<  1: Y-axis deflection
    MSC_JOY_AXES_Z,         ///<  2: Z-axis deflection
    MSC_JOY_AXES_RX,        ///<  3: Rotation about X-axis
    MSC_JOY_AXES_RY,        ///<  4: Rotation about Y-axis
    MSC_JOY_AXES_RZ,        ///<  5: Rotation about Z-axis
    MSC_JOY_AXES_S1,        ///<  6: Slider 1
    MSC_JOY_AXES_S2,        ///<  7: Slider 2
    MSC_JOY_AXES_P1,        ///<  8: POV 1
    MSC_JOY_AXES_P2,        ///<  9: POV 2
    MSC_JOY_AXES_P3,        ///< 10: POV 3
    MSC_JOY_AXES_P4,        ///< 11: POV 4
    MSC_JOY_AXES_P5,        ///< 12: POV 5
    MSC_JOY_AXES_P6,        ///< 13: POV 6
    MSC_JOY_AXES_P7,        ///< 14: POV 7
    MSC_JOY_AXES_P8         ///< 15: POV 8
};

////////////////////////////////////////////////////////////////////////////////

struct MSc_JoyData
{
    double  dAxis[MSC_MAX_AXIS_COUNT];  ///< <-1.0;1.0>
    int     iButt[MSC_MAX_BUTT_COUNT];  ///< 0: released, 1: pressed

    int     iAxisCount;     ///< number of device axis
    int     iButtCount;     ///< number of devise buttons

    int     iActive;        ///<
    int     iForce;         ///< specifies if Force Feddback capable device

    char    acName[522];    ///< device name
};

////////////////////////////////////////////////////////////////////////////////

struct MSc_JoyForce
{
    double  dForceX;        ///< <-1.0;1.0> normalized force
    double  dForceY;        ///< <-1.0;1.0> normalized force
};

////////////////////////////////////////////////////////////////////////////////
// CLASS DOCUMENTATION                                                        //
////////////////////////////////////////////////////////////////////////////////

/** @author Marek Cel
  * @see http://www.cs.cmu.edu/~jparise/directx/joystick/ */
class MSc_Joys
{
////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBERS                                                            //
////////////////////////////////////////////////////////////////////////////////
private:

#   ifdef WIN32
    HWND            WinID;
#   endif

    MSc_JoyForce    Forces[MSC_MAX_JOYS_COUNT];

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS                                                           //
////////////////////////////////////////////////////////////////////////////////
public:

/** Default constructor.
  * @param pWinID platform dependent window identifier (used only in MS Win) */
    MSc_Joys( void *pWinID = 0 );

    virtual ~MSc_Joys( void );

////////////////////////////////////////////////////////////////////////////////

    void startForces( void );

    void stopForces( void );

    void update( void );

////////////////////////////////////////////////////////////////////////////////
// ACCESSORS                                                                  //
////////////////////////////////////////////////////////////////////////////////

    int  getJoyCount( void );

    int  getJoyData( int iJoyNum, MSc_JoyData &JoyData );

////////////////////////////////////////////////////////////////////////////////
// MUTATORS                                                                   //
////////////////////////////////////////////////////////////////////////////////

    void setForceX( int iJoyNum, double dForceNorm );

    void setForceY( int iJoyNum, double dForceNorm );

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS                                                          //
////////////////////////////////////////////////////////////////////////////////
private:

    void clean( void );

    void init( void );

#ifdef WIN32
    void initForces( int iJoyNum );

/** @see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx */
    void initForceX( int iJoyNum );

/** @see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx */
    void initForceY( int iJoyNum );
#endif

    void resetForces( void );

    void updateForces( int iJoyNum );

#ifdef WIN32
/** @see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx */
    void updateForceX( int iJoyNum );

/** @see http://msdn.microsoft.com/en-us/library/windows/desktop/ee417536%28v=vs.85%29.aspx */
    void updateForceY( int iJoyNum );
#endif
};

////////////////////////////////////////////////////////////////////////////////
// DIRECT INPUT CALLBACKS                                                     //
////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32

BOOL CALLBACK enumJoysCallback( const DIDEVICEINSTANCE* pDevInst, VOID* pContext );
BOOL CALLBACK enumAxesCallback( const DIDEVICEOBJECTINSTANCE* pDevObjInst, VOID* pContext );

#endif

////////////////////////////////////////////////////////////////////////////////
// END OF FILE                                                                //
////////////////////////////////////////////////////////////////////////////////

#endif // _MSC_JOYS_H_
