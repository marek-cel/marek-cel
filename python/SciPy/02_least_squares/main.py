#!/usr/bin/env python3

################################################################################

import numpy as np
from scipy import linalg as la

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt

################################################################################

# define true model parameters
x = np.linspace(-1, 1, 100)
a, b, c = 1, 2, 3
y_exact = a + b * x + c * x**2

# simulate noisy data
m = 100
X = 1 - 2 * np.random.rand(m)
Y = a + b * X + c * X**2 + np.random.randn(m)

# fit the data to the model using linear least square
A = np.vstack([X**0, X**1, X**2])  # see np.vander for alternative
sol, r, rank, sv = la.lstsq(A.T, Y)

y_fit = sol[0] + sol[1] * x + sol[2] * x**2

# 1st order polynomial
A = np.vstack([X**n for n in range(2)])
sol, r, rank, sv = la.lstsq(A.T, Y)
y_fit1 = sum([s * x**n for n, s in enumerate(sol)])

# 15th order polynomial
A = np.vstack([X**n for n in range(16)])
sol, r, rank, sv = la.lstsq(A.T, Y)
y_fit15 = sum([s * x**n for n, s in enumerate(sol)])

################################################################################

fig, ax = plt.subplots()

ax.plot(x, y_exact, label = "exact", color = "red")
ax.scatter(x, Y, label = "data", color = "blue")
ax.plot(x, y_fit, label = "fitted", color = "blue")
ax.plot(x, y_fit1, label = "1st order", color = "orange")
ax.plot(x, y_fit15, label = "15th order", color = "green")

ax.set_xlabel("x")
ax.set_ylabel("y")

ax.legend()

plt.ion()
plt.show()

input("Press Enter to continue")