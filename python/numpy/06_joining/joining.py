#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

arr1 = np.array([1, 2, 3])
arr2 = np.array([4, 5, 6])

print()
print(arr1)
print(arr2)

arr3 = np.concatenate((arr1, arr2))

print()
print(arr3)

################################################################################

print("\n*******************")

################################################################################

arr4 = np.array([[1, 2], [3, 4]])
arr5 = np.array([[5, 6], [7, 8]])

print()
print(arr4)
print(arr5)

arr6 = np.concatenate((arr4, arr5), axis=1)
arr7 = np.concatenate((arr4, arr5), axis=0)

print()
print(arr6)
print()
print(arr7)

################################################################################

print("\n*******************")

################################################################################

arr8 = np.array([1, 2, 3])
arr9 = np.array([4, 5, 6])

print()
print(arr8)
print(arr9)

arr10 = np.hstack((arr8, arr9))
arr11 = np.vstack((arr8, arr9))
arr12 = np.dstack((arr8, arr9))

print()
print(arr10)

print()
print(arr11)

print()
print(arr12)

################################################################################
