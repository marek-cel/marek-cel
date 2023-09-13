#!/usr/bin/env python3

################################################################################

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

import numpy as np

################################################################################

x = np.linspace(-5.0, 5.0, 5)
y = np.ones_like(x)


def axes_setting(fig, ax, title, ymax):
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_ylim(0, ymax+1)
    ax.set_title(title)


fig, axes = plt.subplots(1, 4, figsize = (16, 3))

################################################################################

# line widths
linewidths = [0.5, 1.0, 2.0, 4.0]

for n, linewidth in enumerate(linewidths):
    axes[0].plot(x, y + n, color="blue", linewidth=linewidth)

axes_setting(fig, axes[0], "Lines width", len(linewidths))

#line styles
linestyles = ['-', '-.', ':']

for n, linestyle in enumerate(linestyles):
    axes[1].plot(x, y + n, color="blue", lw=2, linestyle=linestyle)

# custom line style
line, = axes[1].plot(x, y + 3, color="blue", lw=2)
length1, gap1, length2, gap2 = 10, 7, 20, 7
line.set_dashes([length1, gap1, length2, gap2])

axes_setting(fig, axes[1], "Lines stytle", len(linestyles) + 1)

# markers
markers = ['+', 'o', '*', 's', '.', '1', '2', '3', '4']

for n, marker in enumerate(markers):
    axes[2].plot(x, y + n, color="blue", lw=2, ls=' ', marker=marker)

axes_setting(fig, axes[2], "Markers", len(markers))

# markers size and color
markersizecolor = [(4, "white"), (8, "red"), (12, "yellow"), (16, "lime")]

for n, (markersize, markerfacecolor) in enumerate(markersizecolor):
    axes[3].plot(x, y + n, color="blue", lw=2, ls='-', marker='o', markersize=markersize, markerfacecolor=markerfacecolor, markeredgewidth=2)

axes_setting(fig, axes[3], "Markers size and color", len(markers))

################################################################################

fig.show()

input("Press Enter to continue")
