#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

################################################################################

x = sympy.Symbol("x")
y = sympy.Symbol("y")
z = sympy.Symbol("z")

a, b = sympy.symbols("a, b", positive = True)

################################################################################

expr = x**2 - 1

print()
print(expr)
print(sympy.factor(expr))

input("Press Enter to continue")

################################################################################

expr = x * sympy.cos(y)  + sympy.sin(z) * x

print()
print(expr)
print(sympy.factor(expr))

input("Press Enter to continue")

################################################################################

expr = sympy.log(a) - sympy.log(b)

print()
print(expr)
print(sympy.logcombine(expr))

input("Press Enter to continue")

################################################################################

expr = x + y + x*y*z

print()
print(expr)
print(expr.collect(x))
print(sympy.collect(expr, y))
