#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

################################################################################

x = sympy.Symbol("x")

a, b = sympy.symbols("a, b")

################################################################################

f = sympy.Function("f")(x)

print()
print(sympy.integrate(f, x))

input("Press Enter to continue")

################################################################################

expr = sympy.sin(x)

print()
print(sympy.integrate(expr, x))
print(sympy.integrate(expr, (x, a ,b))) # defined integral

input("Press Enter to continue")

################################################################################

expr = sympy.sin(x)

i = sympy.Integral(expr, x)

print()
print(i)
print(i.doit())
