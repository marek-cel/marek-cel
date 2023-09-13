#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

sympy.init_printing()

x = sympy.Symbol("x")
y = sympy.Symbol("y")

################################################################################

expr = x**2 + 2*x -3

print()
print(expr)
print(sympy.solve(expr, x))

input("Press Enter to continue")

################################################################################

eq1 = x + 2*y -1
eq2 = x - y + 1

print()
print(eq1)
print(eq2)
print(sympy.solve([eq1, eq2], [x, y]))
print(sympy.solve([eq1, eq2], [x, y], dict = True))

input("Press Enter to continue")
   
