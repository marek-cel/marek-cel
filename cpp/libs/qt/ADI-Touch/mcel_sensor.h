#ifndef _MCEL_SENSOR_H_
#define _MCEL_SENSOR_H_

////////////////////////////////////////////////////////////////////////////////

#define MCEL_SENSOR_MEAN_STEPS 3

////////////////////////////////////////////////////////////////////////////////

#include <qaccelerometer.h>

////////////////////////////////////////////////////////////////////////////////

QTM_USE_NAMESPACE

////////////////////////////////////////////////////////////////////////////////

/** @author Marek Cel (mcel@mcel.pl) */
class mcel_Sensor
{
private:

    QAccelerometer *pSensor;    ///<

    double  dRoll;              ///< [rad]
    double  dPitch;             ///< [rad]

    double  dX[MCEL_SENSOR_MEAN_STEPS];
    double  dY[MCEL_SENSOR_MEAN_STEPS];
    double  dZ[MCEL_SENSOR_MEAN_STEPS];
    
public:

    /** */
    mcel_Sensor();
    
    /** */
    virtual ~mcel_Sensor();

    void update();


    double  getRoll  ( void ) { return dRoll;  }
    double  getPitch ( void ) { return dPitch; }
};

////////////////////////////////////////////////////////////////////////////////

#endif // _MCEL_SENSOR_H_
