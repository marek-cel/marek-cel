#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

################################################################################

x = sympy.Symbol("x")
y = sympy.Symbol("y")

a, b = sympy.symbols("a, b", positive = True)

################################################################################

expr = (1 + x)*(2 + x)

print()
print(expr)
print(sympy.expand(expr))

input("Press Enter to continue")

################################################################################

expr = sympy.sin(x + y)

print()
print(expr)
print(sympy.expand(expr, trig = True))

input("Press Enter to continue")

################################################################################

expr = sympy.log(a * b)

print()
print(expr)
print(sympy.expand(expr, log = True))

input("Press Enter to continue")

################################################################################

expr = sympy.exp(I*a + b)

print()
print(expr)
print(sympy.expand(expr, complex = True))
