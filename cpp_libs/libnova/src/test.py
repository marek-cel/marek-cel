#!/usr/bin/env python3

import datetime
import ephem
import math

year   = 2024
month  = 4
day    = 24
hour   = 17 + 2
minute = 15
second = 30
dt = datetime.datetime(year, month ,day, hour, minute, second)
# sun = ephem.Sun()
# moon = ephem.Moon()
# sun.compute(dt, epoch='2000')
# moon.compute(dt, epoch='2000')

print()
print("date: ", str(ephem.Date(dt)))
print("jd: ", str(ephem.julian_date(dt)))

warsaw = ephem.city("Warsaw")
warsaw.date = ephem.julian_date(dt)

lon = math.degrees(warsaw.lon)
lat = math.degrees(warsaw.lat)

sun = ephem.Sun()
sun.compute(warsaw)

moon = ephem.Moon()
moon.compute(warsaw)

print()
print("LST: ", float(warsaw.sidereal_time()))
print("lat: ", float(lat))
print("lon: ", float(lon))

# results in degrees

print()
print("Sun position:")
# print("RA: ", math.degrees(float(sun.ra)))
# print("dec: ", math.degrees(float(sun.dec)))
print("  Azimuth:   ", math.degrees(float(sun.az)))
print("  Elevation: ", math.degrees(float(sun.alt)))

print()
print("Moon position:")
# print("RA: ", math.degrees(float(moon.ra)))
# print("dec: ", math.degrees(float(moon.dec)))
print("  Azimuth:   ", math.degrees(float(moon.az)))
print("  Elevation: ", math.degrees(float(moon.alt)))

# print()
# print("Moon:")
# print("RA: ", float(moon.ra))
# print("dec: ", float(moon.dec))

# print("RA: ", float(sun.ra))
# print("dec: ", float(sun.dec))
# print("az: ", float(sun.az))
# print("el: ", float(sun.alt))
