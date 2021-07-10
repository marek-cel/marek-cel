#include <math.h>

#include "mcel_sensor.h"

////////////////////////////////////////////////////////////////////////////////

mcel_Sensor::mcel_Sensor() :
    pSensor ( 0 )
{
    pSensor = new QAccelerometer();

    pSensor->start();
}

////////////////////////////////////////////////////////////////////////////////

mcel_Sensor::~mcel_Sensor()
{
    if ( pSensor ) delete pSensor; pSensor = 0;
}

////////////////////////////////////////////////////////////////////////////////

void mcel_Sensor::update()
{
    for ( int i = MCEL_SENSOR_MEAN_STEPS - 1; i > 0; i = i - 1 )
    {
        dX[i] = dX[i-1];
        dY[i] = dY[i-1];
        dZ[i] = dZ[i-1];
    }

    QAccelerometerReading *pReading = pSensor->reading();

    dX[0] = pReading->x();
    dY[0] = pReading->y();
    dZ[0] = pReading->z();

    double dX_Mean = 0.0;
    double dY_Mean = 0.0;
    double dZ_Mean = 0.0;

    for ( int i = 0; i < MCEL_SENSOR_MEAN_STEPS; i++ )
    {
        dX_Mean += dX[i];
        dY_Mean += dY[i];
        dZ_Mean += dZ[i];
    }

    dX_Mean /= (double)MCEL_SENSOR_MEAN_STEPS;
    dY_Mean /= (double)MCEL_SENSOR_MEAN_STEPS;
    dZ_Mean /= (double)MCEL_SENSOR_MEAN_STEPS;

    dRoll  = 0.0;
    dPitch = 0.0;

    if ( fabs(dX_Mean) > fabs(dY_Mean) )
    {
        dPitch = - atan2( dZ_Mean, fabs(dX_Mean) );
    }
    else
    {
        dPitch = - atan2( dZ_Mean, fabs(dY_Mean) );
    }

    dRoll = atan2( dY_Mean, dX_Mean );
}
