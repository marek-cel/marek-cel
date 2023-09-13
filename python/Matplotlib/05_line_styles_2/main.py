#!/usr/bin/env python3

################################################################################

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

import numpy as np
import sympy

################################################################################

sym_x = sympy.Symbol("x")
x = np.linspace(-2 * np.pi, 2 * np.pi, 100)


def sin_expansion(x, n):
    return sympy.lambdify(sym_x, sympy.sin(sym_x).series(n=n+1).removeO(), "numpy")(x)


fig, ax = plt.subplots(figsize=(10,6))

ax.plot(x, np.sin(x), linewidth=4, color="red", label="sin(x)")

colors = ["blue", "black"]
linestyles = ['-', '-.', ':']

for idx, n in enumerate(range(1, 12, 2)):
    ax.plot(x, sin_expansion(x, n), color=colors[idx // 3],
            linestyle=linestyles[idx % 3],
            linewidth=3,
            label="Approximadion of order O(%d)" % (n+1))

ax.set_ylim(-1.1, 1.1)
ax.set_xlim(-1.5*np.pi, 1.5*np.pi)

ax.legend(bbox_to_anchor=(1.02, 1), loc=2, borderaxespad=0.0)

fig.subplots_adjust(right=0.75)

fig.show()

input("Press Enter to continue")
