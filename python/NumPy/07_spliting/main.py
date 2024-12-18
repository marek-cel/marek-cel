#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

arr1 = np.array([1, 2, 3, 4, 5, 6])

arr2 = np.array_split(arr1, 3)
arr3 = np.array_split(arr1, 4)

print()
print(arr1)
print(arr2)
print(arr3)

input("Press Enter to continue")

################################################################################

arr4 = np.array([[1, 2], [3, 4], [5, 6], [7, 8], [9, 10], [11, 12]])

arr5 = np.array_split(arr4, 3)

print()
print(arr4)
print()
print(arr5)
