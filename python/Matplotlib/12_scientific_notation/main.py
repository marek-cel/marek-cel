#!/usr/bin/env python3

################################################################################

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

import numpy as np
import sympy

################################################################################

x = np.linspace(0, 1e5, 100)
y = x ** 2

fig, axes = plt.subplots(1, 2, figsize=(8, 3))

axes[0].plot(x, y, 'b.')
axes[0].set_title("default labels", loc='right')

axes[1].plot(x, y, 'b')
axes[1].set_title("scientific notation labels", loc='right')

formatter = mpl.ticker.ScalarFormatter(useMathText=True)
formatter.set_scientific(True)
formatter.set_powerlimits((-1,1))
axes[1].xaxis.set_major_formatter(formatter)
axes[1].yaxis.set_major_formatter(formatter)

fig.show()

input("Press Enter to continue")
