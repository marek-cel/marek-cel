#!/usr/bin/env python3

################################################################################

import numpy as np
from scipy import linalg as la

import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt

################################################################################

# define a function, desired tolerance and starting interval [a, b]
f = lambda x: np.exp(x) - 2
fp = lambda x: np.exp(x)
tol = 0.01
a, b = -2, 2
x = np.linspace(-2.1, 2.1, 1000)

# graph the function f
fig, ax = plt.subplots()

ax.plot(x, f(x), lw=1.5)
ax.grid()

x = a
fx = f(x)
fpx = fp(x)

n = 1
while abs(fx) > tol and n < 20:
    a = fpx
    b = fx - a*x
    x = -b/a
    fx = f(x)
    fpx = fp(x)
    n += 1

print("n= ", n, " x= ", x, " fx= ", fx)

ax.plot(x, fx, 'r*', markersize=10)

plt.ion()
plt.show()

input("Press Enter to continue")