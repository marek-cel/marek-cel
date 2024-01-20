#!/usr/bin/env python3

################################################################################

import datetime

x = datetime.datetime.now()

print(x)
print(x.year)
print(x.strftime("%A"))

################################################################################

import time
import pendulum

################################################################################

print()

dt1 = pendulum.datetime(2021, 7, 25, tz="Europe/Warsaw")

print(dt1)
print(dt1.timezone.name)

dt2 = dt1.in_timezone("America/New_York")
print(dt2)

dt3 = pendulum.now()
print(dt3)

################################################################################
