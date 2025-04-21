#include <iostream>
#include <ctime>
#include <iomanip>

#include <libnova/libnova.h>

// Function to print horizontal coordinates (azimuth and elevation)
void printHorizontalCoordinates(const char* name, struct ln_hrz_posn* hrz)
{
    std::cout << name << " position:" << std::endl;
    std::cout << "  Azimuth:   " << std::fixed << std::setprecision(6) << hrz->az << " degrees" << std::endl;
    std::cout << "  Elevation: " << std::fixed << std::setprecision(6) << hrz->alt << " degrees" << std::endl;
    std::cout << std::endl;
}

int main()
{
    // Observer's location (example: New York City)
    double observer_lat = 40.7128;  // latitude in degrees (North is positive)
    double observer_lng = -74.0060; // longitude in degrees (East is positive)
    double observer_alt = 10.0;     // altitude in meters

    // Get current time
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = gmtime(&rawtime); // Use UTC time

    // Convert to Julian Day
    struct ln_date date;
    date.years = timeinfo->tm_year + 1900;
    date.months = timeinfo->tm_mon + 1;
    date.days = timeinfo->tm_mday;
    date.hours = timeinfo->tm_hour;
    date.minutes = timeinfo->tm_min;
    date.seconds = timeinfo->tm_sec;

    double JD = ln_get_julian_day(&date);

    // Print current date and time
    std::cout << "Calculating celestial positions for:" << std::endl;
    std::cout << "Date: " << date.years << "-" << date.months << "-" << date.days << std::endl;
    std::cout << "Time: " << date.hours << ":" << date.minutes << ":" << date.seconds << " UTC" << std::endl;
    std::cout << "Observer location: Lat " << observer_lat << "°, Lng " << observer_lng << "°, Alt " << observer_alt << "m" << std::endl;
    std::cout << std::endl;

    // Calculate Sun's position
    struct ln_equ_posn sun_equ;
    struct ln_hrz_posn sun_hrz;

    // Get equatorial coordinates for the Sun
    ln_get_solar_equ_coords(JD, &sun_equ);

    // Convert to horizontal coordinates (azimuth and elevation)
    struct ln_lnlat_posn observer_position = {observer_lng, observer_lat};
    ln_get_hrz_from_equ(&sun_equ, &observer_position, JD, &sun_hrz);

    // Calculate Moon's position
    struct ln_equ_posn moon_equ;
    struct ln_hrz_posn moon_hrz;

    // Get equatorial coordinates for the Moon
    ln_get_lunar_equ_coords(JD, &moon_equ);

    ln_get_hrz_from_equ(&moon_equ, &observer_position, JD, &moon_hrz);

    // Print results
    printHorizontalCoordinates("Sun", &sun_hrz);
    printHorizontalCoordinates("Moon", &moon_hrz);

    return 0;
}