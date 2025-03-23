/*
Module : AAMoonNodes2.cpp
Purpose: Implementation for the algorithms which obtain the dates when the Moon passes thro its nodes (revised version)
Created: PJN / 16-11-2019
History: PJN / 16-11-2019 1. Initial implementation
         PJN / 27-06-2022 1. Updated all the code in AAMoonNodes2.cpp to use C++ uniform initialization for all 
                          variable declarations.
         PJN / 24-07-2024 1. Fixed an edge case bug in all the Calculate function of CAAMoonNodes2 where the main loop
                          iterates from StartJD by StepInterval until JD < EndJD. That means that events happening closer than
                          StepInterval to EndJD get lost because the step where we can catch it is outside of StartJD...EndJD
                          interval. Now the code iterates from StartJD by StepInterval until JD < (EndJD+StepInterval). Thanks
                          to Alexander Vasenin for reporting this issue.

Copyright (c) 2019 - 2025 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

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
#include "AAMoonNodes2.h"
#include "AAMoon.h"
#ifndef AAPLUS_NO_ELP2000
#include "AAELP2000.h"
#endif //#ifndef AAPLUS_NO_ELP2000
#ifndef AAPLUS_NO_ELPMPP02
#include "AAELPMPP02.h"
#endif //#ifndef AAPLUS_NO_ELPMPP02
#include <cassert>


//////////////////// Implementation ///////////////////////////////////////////

std::vector<CAAMoonNodesDetails2> CAAMoonNodes2::Calculate(double StartJD, double EndJD, double StepInterval, Algorithm algorithm)
{
  //What will be the return value
  std::vector<CAAMoonNodesDetails2> events;

  double JD{StartJD};
  double LastJD0{0};
  double LastLatitude0{-90};
  const double localEndJD{EndJD + StepInterval}; //Make sure we do not miss any possible events near to EndJD
  while (JD < localEndJD)
  {
    double MoonLatitude{0};
    switch (algorithm)
    {
      case Algorithm::MeeusTruncated:
      {
        MoonLatitude = CAAMoon::EclipticLatitude(JD);
        break;
      }
#ifndef AAPLUS_NO_ELP2000
      case Algorithm::ELP2000:
      {
        MoonLatitude = CAAELP2000::EclipticLatitude(JD);
        break;
      }
#endif //#ifndef AAPLUS_NO_ELP2000
#ifndef AAPLUS_NO_ELPMPP02
      case Algorithm::ELPMPP02Nominal:
      {
        MoonLatitude = CAAELPMPP02::EclipticLatitude(JD, CAAELPMPP02::Correction::Nominal);
        break;
      }
      case Algorithm::ELPMPP02LLR:
      {
        MoonLatitude = CAAELPMPP02::EclipticLatitude(JD, CAAELPMPP02::Correction::LLR);
        break;
      }
      case Algorithm::ELPMPP02DE405:
      {
        MoonLatitude = CAAELPMPP02::EclipticLatitude(JD, CAAELPMPP02::Correction::DE405);
        break;
      }
      case Algorithm::ELPMPP02DE406:
      {
        MoonLatitude = CAAELPMPP02::EclipticLatitude(JD, CAAELPMPP02::Correction::DE406);
        break;
      }
#endif //#ifndef AAPLUS_NO_ELPMPP02
      default:
      {
        assert(false);
        break;
      }
    }

    if (LastLatitude0 != -90)
    {
      if ((LastLatitude0 < 0) && (MoonLatitude >= 0))
      {
        CAAMoonNodesDetails2 event;
        event.type = CAAMoonNodesDetails2::Type::Ascending;
        const double fraction{(0 - LastLatitude0) / (MoonLatitude - LastLatitude0)};
        event.JD = LastJD0 + (fraction*StepInterval);
        if (event.JD < EndJD)
          events.push_back(event);
      }
      else if ((LastLatitude0 > 0) && (MoonLatitude <= 0))
      {
        CAAMoonNodesDetails2 event;
        event.type = CAAMoonNodesDetails2::Type::Descending;
        const double fraction{(0 - LastLatitude0) / (MoonLatitude - LastLatitude0)};
        event.JD = LastJD0 + (fraction*StepInterval);
        if (event.JD < EndJD)
          events.push_back(event);
      }
    }

    //Prepare for the next loop
    LastLatitude0 = MoonLatitude;
    LastJD0 = JD;
    JD += StepInterval;
  }

  return events;
}
