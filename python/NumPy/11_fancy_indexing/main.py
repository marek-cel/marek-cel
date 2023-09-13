#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

a1 = np.linspace(0,10,11)

print()
print(a1)

input("Press Enter to continue")

################################################################################

a2 = a1[np.array([1,2,3])]
print()
print(a2)

input("Press Enter to continue")

################################################################################

a3 = a1[[9,8,3]]
print()
print(a3)

input("Press Enter to continue")

################################################################################

temp = [0,1,2]
a4 = a1[temp]
print()
print(a4)

input("Press Enter to continue")

################################################################################

temp = [True, False, False, False, False, False, False, False, False, False, True]
a5 = a1[temp]
print()
print(a5)

input("Press Enter to continue")