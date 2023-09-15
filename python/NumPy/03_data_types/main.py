#!/usr/bin/env python3

################################################################################

import numpy as np

################################################################################

# i - integer
# b - boolean
# u - unsigned integer
# f - float
# c - complex float
# m - timedelta
# M - datetime
# O - object
# S - string
# U - unicode string
# V - fixed chunk of memory for other type ( void )

################################################################################

# Create an array with data type string

arr1 = np.array([1, 2, 3, 4], dtype='S')

print()
print(arr1)
print(arr1.dtype)

input("Press Enter to continue")

################################################################################

# Create an array with data type 4 bytes integer:

arr2 = np.array([1, 2, 3, 4], dtype='i4')

print()
print(arr2)
print(arr2.dtype)

arr21 = np.array([1, 2, 3, 4], dtype=np.int32)

print()
print(arr21)
print(arr21.dtype)

input("Press Enter to continue")

################################################################################

# Change data type from float to integer by using 'i' as parameter value:

arr3 = np.array([1.1, 2.1, 3.1])

newarr = arr3.astype('i')

print()
print(newarr)
print(newarr.dtype)

input("Press Enter to continue")

################################################################################

# Create an array with data type complex:

arr4 = np.array([1, 2, 3, 4], dtype=complex)

print()
print(arr4)
print(arr4.dtype)
