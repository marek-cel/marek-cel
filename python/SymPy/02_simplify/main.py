#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

################################################################################

x = sympy.Symbol("x")

################################################################################

expr = 2 * (x**2 - x) - x * (x + 1)
print(expr)
print(sympy.simplify(expr))

input("Press Enter to continue")

################################################################################

expr = sympy.sin(x)**2 + sympy.cos(x)**2
print(expr)
print(sympy.simplify(expr))

input("Press Enter to continue")

################################################################################

expr = 2 * sympy.cos(x) * sympy.sin(x)
print(expr)
print(sympy.trigsimp(expr))
