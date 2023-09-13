#!/usr/bin/env python3

################################################################################

import numpy as np
import sympy
from sympy import I, pi, oo

sympy.init_printing()

x = sympy.Symbol("x")
y = sympy.Symbol("y")
z = sympy.Symbol("z")

a, b = sympy.symbols("a, b", positive = True)

################################################################################

expr = 1 + pi

print()
print(expr)
print(sympy.N(expr))
print(sympy.N(expr, 50))
print(sympy.N(expr, 3))

print(expr.evalf())
print(expr.evalf(50))
print(expr.evalf(3))

input("Press Enter to continue")

################################################################################

expr_func = sympy.lambdify(x, expr)
print()
print(expr_func(1.0))

expr_func = sympy.lambdify(x, expr, 'numpy')
xvalues = np.arange(0,10)
print()
print(xvalues)
print(expr_func(xvalues))

input("Press Enter to continue")

