#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

sympy.init_printing()

x = sympy.Symbol("x")
y = sympy.Symbol("y")
z = sympy.Symbol("z")

f = sympy.Function('f')(x)
g = sympy.Function('g')(x, y)

################################################################################

print()
print(sympy.diff(f, x))
print(sympy.diff(f, x, x))
print(sympy.diff(f, x, 3))

input("Press Enter to continue")

################################################################################

print()
print(sympy.diff(g, x))
print(sympy.diff(g, x, y))

print()
print(g.diff(x))
print(g.diff(x, y))

input("Press Enter to continue")

################################################################################

expr = 2*x**2 + 3*x + 7

print()
print(expr.diff(x))

input("Press Enter to continue")

################################################################################

expr = sympy.exp(sympy.sin(x))

d = sympy.Derivative(expr, x)

print()
print(d)
print(d.doit())


