#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

################################################################################

x, a, b, c = sympy.symbols("x, a, b, c")

solution = sympy.solve(a + b*x + c*x**2, x)
print()
print(solution)

solution = sympy.solve(a * sympy.cos(x) - b * sympy.sin(x), x)
print()
print(solution)

# non-solvable
solution = sympy.solve(sympy.sin(x)-x, x)
print()
print(solution)

# input("Press Enter to continue")
