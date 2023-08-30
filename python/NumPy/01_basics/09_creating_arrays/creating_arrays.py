#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

arr1 = np.array([10, 11, 12, 13, 14, 15])
print()
print(arr1)

input("Press Enter to continue")

################################################################################

arr2 = np.zeros((2,3))
print()
print(arr2)

input("Press Enter to continue")

################################################################################

arr31 = np.ones((2,3))
print()
print(arr31)

arr32 = np.ones(3)
print()
print(arr32)

input("Press Enter to continue")

################################################################################

arr41 = np.full(3,9)
print()
print(arr41)

arr42 = np.full((3,3),9)
print()
print(arr42)

input("Press Enter to continue")

################################################################################

arr51 = np.diag((1,1,1))
print()
print(arr51)

arr52 = np.diag((1,1,1),-2)
print()
print(arr52)

arr53 = np.diag((1,1,1),2)
print()
print(arr53)

input("Press Enter to continue")

################################################################################

arr6 = np.empty((2,3),dtype=float)
print()
print(arr6)

input("Press Enter to continue")

################################################################################

arr7 = np.zeros_like(arr51)
print()
print(arr7)

input("Press Enter to continue")
