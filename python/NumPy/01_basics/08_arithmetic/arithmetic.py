#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

arr1 = np.array([
    [1,2,3],
    [4,5,6],
    [7,8,9]
])

arr2 = arr1.copy()

mat1 = np.asmatrix(arr1)
mat2 = np.asmatrix(arr2)

print(arr1)
print(arr2)

input("Press Enter to continue")

################################################################################

arr31 = np.add(arr1, arr2)
arr32 = arr1 + arr2

print()
print("add")
print(arr31)
print(arr32)

input("Press Enter to continue")

################################################################################

arr41 = np.subtract(arr1, arr2)
arr42 = arr1 - arr2

print()
print("subtract")
print(arr41)
print(arr42)

input("Press Enter to continue")

################################################################################

arr51 = np.multiply(arr1, arr2)
arr52 = arr1 * arr2

print()
print("multiply")
print(arr51)
print(arr52)

input("Press Enter to continue")

################################################################################

arr61 = np.divide(arr1, arr2)
arr62 = arr1 / arr2

print()
print("divide")
print(arr61)
print(arr62)

input("Press Enter to continue")

################################################################################

arr6 = np.dot(arr1, arr2)
mat6 = mat1 * mat2

print()
print("dot")
print(arr6)
print(mat6)

input("Press Enter to continue")

################################################################################

arr61 = np.power(arr1, arr2)
arr62 = arr1 ** arr2

print()
print("power")
print(arr61)
print(arr62)

input("Press Enter to continue")

################################################################################
