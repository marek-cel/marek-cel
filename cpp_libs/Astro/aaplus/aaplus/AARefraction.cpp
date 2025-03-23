/*
Module : AARefraction.cpp
Purpose: Implementation for the algorithms which model Atmospheric refraction
Created: PJN / 29-12-2003
History: PJN / 26-11-2010 1. CAARefraction::RefractionFromApparent now returns a constant refraction value for all 
                          altitudes below a certain limit. Thanks to mehrzad khoddam for prompting this update.
                          2. CAARefraction::RefractionFromTrue now returns a constant refraction value for all 
                          altitudes below a certain limit. Thanks to mehrzad khoddam for prompting this update.
         PJN / 05-07-2022 1. Updated all the code in AARefraction.cpp to use C++ uniform initialization for all
                          variable declarations.
         PJN / 18-02-2025 1. Reimplemented CAARefraction::RefractionFromTrue to use the formulae from NOAA at
                          https://gml.noaa.gov/grad/solcalc/calcdetails.html. These formulae provides better 
                          behaviour when the Altitude value is less than 0 degrees.
                          2. Reimplemented CAARefraction::RefractionFromApparent to use RefractionFromTrue so that
                          both functions will now round trip to the same values when using the formula:

                          apparentAltitude = trueAltitude + refractionAmount

Copyright (c) 2003 - 2025 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code.

*/


//////////////////// Includes /////////////////////////////////////////////////

#include "stdafx.h"
#include "AARefraction.h"
#include "AACoordinateTransformation.h"
#include <cmath>


//////////////////// Implementation ///////////////////////////////////////////

double CAARefraction::RefractionFromApparent(double Altitude, double Pressure, double Temperature) noexcept
{
  //Implement RefractionFromApparent in terms of RefractionFromTrue
  double TrueAltitude{Altitude};
  bool bContinue{true};
  double refraction{0};
  while (bContinue)
  {
    refraction = RefractionFromTrue(TrueAltitude, Pressure, Temperature);
    const double newTrueAltitude{Altitude - refraction};
    bContinue = fabs(newTrueAltitude - TrueAltitude) > 0.00001;
    if (bContinue)
      TrueAltitude = newTrueAltitude;
  }
  return refraction;
}

double CAARefraction::RefractionFromTrue(double Altitude, double Pressure, double Temperature) noexcept
{
  if (Altitude > 85)
    return 0;
  else if (Altitude > 84)
  {
    const double Correction{((Pressure/1010) * (283/(273 + Temperature)))};
    return Correction * 0.10177457991197518 / 60 * (85 - Altitude); //Note we use this logic to avoid a discontinuity at 85 degrees
  }
  else if (Altitude > 5.49398) //Note we use 5.49398 instead of 5 here to avoid a discontinuity at 5 degrees
  {
    const double Correction{((Pressure/1010) * (283/(273 + Temperature)))};
    const double h{CAACoordinateTransformation::DegreesToRadians(Altitude)};
    const double tanh{tan(h)};
    const double tanh3{tanh*tanh*tanh};
    const double tanh5{tanh3*tanh*tanh};
    return Correction * ((58.1/tanh) - (0.07/tanh3) + (0.000086/tanh5))/3600;
  }
  else if (Altitude > -0.575)
  {
    const double Correction{((Pressure / 1010) * (283 / (273 + Temperature)))};
    return Correction * (1735 + Altitude*(-518.2 + (Altitude*(103.4 + Altitude*(-12.79 + (Altitude*0.711))))))/3600;
  }
  else
  {
    const double Correction{((Pressure/1010) * (283/(273 + Temperature)))};
    const double h{CAACoordinateTransformation::DegreesToRadians(Altitude)};
    return Correction * (-20.774/tan(h))/3600;
  }
}
