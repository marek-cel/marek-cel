#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

sympy.init_printing()

x = sympy.Symbol("x")
y = sympy.Symbol("y")
z = sympy.Symbol("z")

a, b = sympy.symbols("a, b", positive = True)

################################################################################

expr = 1 / (x**2 + 3*x + 2)

print()
print(expr)
print(sympy.apart(expr, x))

input("Press Enter to continue")

################################################################################

expr = 1 / (x*y  + y) + 1 / (1 + x)

print()
print(expr)
print(sympy.together(expr))

input("Press Enter to continue")

################################################################################

expr = y / (y*x + y)

print()
print(expr)
print(sympy.cancel(expr))

input("Press Enter to continue")

