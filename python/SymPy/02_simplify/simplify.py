#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

sympy.init_printing()

x = sympy.Symbol("x")

expr = 2 * (x**2 - x) - x * (x + 1)
print(expr)
print(sympy.simplify(expr))

input("Press Enter to continue")

################################################################################
