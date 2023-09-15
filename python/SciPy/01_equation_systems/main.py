#!/usr/bin/env python3

################################################################################

import numpy as np
from scipy import linalg as la

################################################################################

A = np.array([[2, 3], [5, 4]])
b = np.array([4, 3])

P, L, U = la.lu(A)

print()
print(L)
print(U)
print(P.dot(L.dot(U)))

x = la.solve(A, b)
print()
print(x)
