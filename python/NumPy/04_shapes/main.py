#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

arr1 = np.array([[1, 2, 3, 4], [5, 6, 7, 8]])

print()
print(arr1.shape)

input("Press Enter to continue")

################################################################################

arr2 = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])

newarr2 = arr2.reshape(4, 3)

print()
print(arr2.shape)
print(newarr2.shape)