#!/usr/bin/env python3

################################################################################

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

import numpy as np
import sympy

################################################################################

fig, ax = plt.subplots(figsize=(12, 3))

ax.set_yticks([])
ax.set_xticks([])

ax.set_xlim(-0.5, 3.5)
ax.set_ylim(-0.05, 0.25)

ax.axhline(0)

ax.text(0, 0.1, "Text label", fontsize=14, family="serif")

ax.plot(1, 0, "o")
ax.annotate("Annotation",
            fontsize=14, family="serif",
            xy=(1, 0), xycoords="data",
            xytext=(+20, +50), textcoords="offset points",
            arrowprops=dict(arrowstyle="->", connectionstyle="arc3, rad=.5"))

ax.text(2, 0.1, r"Equation: $i\hbar\partial_t \Psi = \hat{H}\Psi$", fontsize=14, family="serif")

fig.show()

input("Press Enter to continue")
