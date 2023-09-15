#!/usr/bin/env python3

################################################################################

import sympy
from sympy import I, pi, oo

################################################################################

x, y, z = sympy.symbols("x, y, z")

i11, i12, i13 = sympy.symbols("i11, i12, i13")
i21, i22, i23 = sympy.symbols("i21, i22, i23")
i31, i32, i33 = sympy.symbols("i31, i32, i33")

################################################################################

v1 = sympy.Matrix([x, y, z])
m1 = sympy.Matrix([
    [i11, i12, i13],
    [i21, i22, i23],
    [i31, i32, i33]
])

print()
print(v1)
print(m1)

input("Press Enter to continue")

################################################################################

vr = m1 * v1;

print()
print(vr)
