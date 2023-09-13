#!/usr/bin/env python3

################################################################################

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

import numpy as np
import sympy

################################################################################

x = np.linspace(-5.0, 2.0, 100)
y1 = x**3 + 5*x**2 + 10
y2 = 3*x**2 + 10*x
y3 = 6*x + 10

fig, ax = plt.subplots()

ax.plot(x, y1, label = "y(x)", color = "red")
ax.plot(x, y2, label = "y'(x)", color = "green")
ax.plot(x, y3, label = "y''(x)", color = "blue")

ax.set_xlabel("x")
ax.set_ylabel("y")

ax.legend()

plt.ion()
plt.show()

input("Press Enter to continue")
