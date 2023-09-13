#!/usr/bin/env python3

################################################################################

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

import numpy as np

################################################################################

x = np.linspace(0.0, 1.0, 100)

y1 = x
y2 = x + x**2

fig, ax = plt.subplots(1, 4, figsize = (16, 3))

################################################################################

ax[0].plot(x, y1, label="y(x)=x")
ax[0].plot(x, y2, label="y(x)=x + x**2")
ax[0].legend(loc=1)

ax[1].plot(x, y1, label="y(x)=x")
ax[1].plot(x, y2, label="y(x)=x + x**2")
ax[1].legend(loc=2)

ax[2].plot(x, y1, label="y(x)=x")
ax[2].plot(x, y2, label="y(x)=x + x**2")
ax[2].legend(loc=3)

ax[3].plot(x, y1, label="y(x)=x")
ax[3].plot(x, y2, label="y(x)=x + x**2")
ax[3].legend(loc=4)

fig.show()

################################################################################

x = np.linspace(-1.0, 1.0, 100)

fig, ax = plt.subplots(figsize = (16, 4))

for n in range(1, 9):
    ax.plot(x, x*n, label="x*%d" % n)

ax.legend(bbox_to_anchor=(0.0, 1.0), loc=3, ncol=4)

fig.show()

################################################################################

input("Press Enter to continue")
