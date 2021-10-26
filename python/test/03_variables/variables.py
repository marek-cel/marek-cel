#!/usr/bin/env python3

################################################################################

# Names
# Only letters, digits and underscore are allowed.
# Cannot start with a digit.

variable_1 = 1
_variable2 = 2
#3_variable + 3 # error

################################################################################

# variables names are case-sensitive

a = 1
A = 2

print()
print(a)
print(A)

################################################################################

# Casting

x = str(3)    # "3"
y = int(3)    # 3
z = float(3)  # 3.0

################################################################################

# Getting type

print()
print(type(x))
print(type(y))
print(type(z))

################################################################################

#  Assign multiple values

i, j, k = 1, 2, 3
print()
print(i)
print(j)
print(k)

l = m = n = 666
print()
print(l)
print(m)
print(n)

t = [4, 5, 6]
p, q, r = t;
print()
print(p)
print(q)
print(r)
