#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

arr1 = np.array([1, 2, 3, 4, 5])  # from list
arr2 = np.array((1, 2, 3, 4, 5))  # from tuple

print(arr1)
print(arr2)

input("Press Enter to continue")

################################################################################

# 0-D array

arr0D = np.array(42)

print()
print("arr0D", arr0D)

input("Press Enter to continue")

################################################################################

# 1-D array

arr1D = np.array([1, 2, 3, 4, 5])

print()
print("arr1D", arr1D)

input("Press Enter to continue")

################################################################################

# 2-D array

arr2D = np.array([[1, 2, 3], [4, 5, 6]])

print()
print("arr2D", arr2D)

input("Press Enter to continue")

################################################################################

# 3-D array

arr3D = np.array([[[11, 12, 13], [14, 15, 16]], [[21, 22, 23], [24, 25, 26]]])

print()
print("arr3D", arr3D)

input("Press Enter to continue")

################################################################################

print()
print("arr0D.ndim", arr0D.ndim)
print("arr1D.ndim", arr1D.ndim)
print("arr2D.ndim", arr2D.ndim)
print("arr3D.ndim", arr3D.ndim)

input("Press Enter to continue")

################################################################################

print()
print("arr1D[0]", arr1D[0])
print("arr1D[1]", arr1D[1])

input("Press Enter to continue")

################################################################################

print()
print(arr1D[0:2])
print(arr1D[:2])
print(arr1D[2:])
print(arr1D[1:3])

input("Press Enter to continue")
