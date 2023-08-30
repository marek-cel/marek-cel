#!/usr/bin/env python3

################################################################################

import matplotlib as mpl
import matplotlib.pyplot as plt

import numpy as np

################################################################################

print(mpl.__version__)

################################################################################

xpoints = np.linspace(0, 2.0 * np.pi, 100)
ypoints = np.sin(xpoints)

plt.plot(xpoints, ypoints)
plt.show()

################################################################################
