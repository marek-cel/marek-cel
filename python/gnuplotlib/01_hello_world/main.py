#!/usr/bin/env python3

################################################################################

import gnuplotlib as gp
import numpy      as np

################################################################################

xpoints = np.linspace(0, 2.0 * np.pi, 100)
ypoints = np.sin(xpoints)

gp.plot(xpoints, ypoints)

################################################################################