#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

################################################################################

A = sympy.Matrix([[2, 3], [5, 4]])
b = sympy.Matrix([4, 3])

L, U, _ = A.LUdecomposition()

print()
print(L)
print(U)
print(L * U)

x = A.solve(b); x  # equivalent to A.LUsolve(b)

print()
print(x)

input("Press Enter to continue")

################################################################################

p = sympy.symbols("p", positive=True)
A = sympy.Matrix([[1, sympy.sqrt(p)], [1, 1/sympy.sqrt(p)]])
b = sympy.Matrix([1, 2])
x = A.solve(b)

print()
print(x)
