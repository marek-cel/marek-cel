#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

#include <AA+.h>

#include <units.h>

using namespace std;

using namespace units::literals;

struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    double second;
};

void GetSolarRaDecByJulian(double JD, bool bHighPrecision, double& RA, double& Dec);
double GetJulianDate(const DateTime& gd);

int main()
{
    std::cout << "Hello, aaplus!" << std::endl;

    DateTime DT;
    // DT.year = 2025;
    // DT.month = 4;
    // DT.day = 24;
    // DT.hour = 17;
    // DT.minute = 15;
    // DT.second = 30.0;

    DT.year = 2000;
    DT.month = 1;
    DT.day = 1;
    DT.hour = 0;
    DT.minute = 0;
    DT.second = 0.0;

    CAADate date;
    date.Set(DT.year, DT.month, DT.day, DT.hour, DT.minute, DT.second, true);
    double JD1 = date.Julian();
    double JD2 = GetJulianDate(DT);
    std::cout << std::setprecision(15);
    std::cout << "JD1: " << JD1 << " JD2: " << JD2
              << " diff: " << JD1 - JD2 << std::endl;

    double RA, Dec;
    GetSolarRaDecByJulian(JD1, true, RA, Dec);
    units::angle::radian_t RA_rad = units::angle::degree_t(RA);
    units::angle::radian_t Dec_rad = units::angle::degree_t(Dec);
    std::cout << "RA: " << RA << " Dec: " << Dec << std::endl;
    std::cout << "RA: " << RA_rad << " Dec: " << Dec_rad << std::endl;

    return 0;



    // GST
    double GST = CAASidereal::MeanGreenwichSiderealTime(JD1);
    std::cout << "GST: " << GST << std::endl;

    // Greenwich sidereal time angle
    units::angle::radian_t GSTAngle = GST * 15.0_deg;

    // Warsaw - local hour angle
    units::angle::radian_t lat = 52.2297_deg;
    units::angle::radian_t lon = 21.0122_deg;
    units::angle::degree_t LHA = GSTAngle + lon - RA * 1.0_deg;

    // convert Ra, Dec to Az, Alt
    double Az, Alt;
    auto result = CAACoordinateTransformation::Equatorial2Horizontal(LHA(), Dec, lat());
    Az = result.X;
    Alt = result.Y;
    std::cout << "Az: " << Az << " Alt: " << Alt << std::endl;


    return 0;
}

void GetSolarRaDecByJulian(double JD, bool bHighPrecision, double& RA, double& Dec)
{
  const double JDSun{CAADynamicalTime::UTC2TT(JD)};
  const double lambda{CAASun::ApparentEclipticLongitude(JDSun, bHighPrecision)};
  const double beta{CAASun::ApparentEclipticLatitude(JDSun, bHighPrecision)};
  const double epsilon{CAANutation::TrueObliquityOfEcliptic(JDSun)};
  CAA2DCoordinate Solarcoord{CAACoordinateTransformation::Ecliptic2Equatorial(lambda, beta, epsilon)};
  RA = Solarcoord.X;
  Dec = Solarcoord.Y;
}

double GetJulianDate(const DateTime& gd)
{
    double jd = 0.0;

    // Meeus J.: Astronomical Algorithms, p.61
    double y = gd.year;
    double m = gd.month;
    double d = gd.day;

    if (m == 1 || m == 2)
    {
        y = y - 1;
        m = 12 + m;
    }

    double a = static_cast<int>(y * 0.01);
    double b = 2.0 - a + static_cast<int>(a * 0.25);

    jd = static_cast<int>(365.25 * (y + 4716.0))
    + static_cast<int>(30.6001 * (m + 1.0))
    + d + b - 1524.5;

    jd += gd.hour   / 24.0;
    jd += gd.minute / (24.0 * 60.0);
    jd += gd.second / (24.0 * 60.0 * 60.0);

    return jd;
}
