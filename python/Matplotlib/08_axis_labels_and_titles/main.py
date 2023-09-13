#!/usr/bin/env python3

################################################################################

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

import numpy as np
import sympy

################################################################################

x = np.linspace(0, 50, 500)
y = np.sin(x) * np.exp(-x/10)

fig, ax = plt.subplots(subplot_kw={'facecolor':"#ebf5ff"})

ax.plot(x, y, lw=2)

ax.set_xlabel("x", labelpad=5, fontsize=18, fontname='serif', color="blue")
ax.set_ylabel("f(x)", labelpad=15, fontsize=18, fontname='serif', color="blue")

ax.set_title("axis labels and title example", fontsize=16, fontname='serif', color="blue")

fig.show()

input("Press Enter to continue")
