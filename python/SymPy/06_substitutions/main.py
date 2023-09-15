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

expr = x + y

print()
print(expr)
print(expr.subs(x, y))

input("Press Enter to continue")

################################################################################

expr = sympy.sin(x * sympy.exp(x))

print()
print(expr)
print(expr.subs(x, y))

input("Press Enter to continue")

################################################################################

dict = {
    z: sympy.exp(y),
    x: y,
    sympy.sin: sympy.cos
}

expr = sympy.sin(x * z)

print()
print(expr)
print(expr.subs(dict))

input("Press Enter to continue")

################################################################################

values = {
    x: 1.25,
    y: 0.4,
    z: 3.2
}

expr = x*y + z**2 * x
print()
print(expr)
print(expr.subs(values))
