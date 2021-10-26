#!/usr/bin/env python3

################################################################################

print("Hello World!")
print('Hello World!')
print("\n\t\"Hello World\"")
print(5*"Hello world ")

################################################################################

first_name = "marek"
last_name  = "cel"

full_name = first_name + " " + last_name

name = " " + full_name

################################################################################

print(name)
print(name.upper())
print(name.title())
print(name.capitalize())
print(name.strip())

################################################################################

if "a" in name :
    print("There is an \"a\" letter in", name)
else :
    print("There isn't an \"a\" letter in", name)

if "w" in name :
    print("There is an \"w\" letter in", name)
else :
    print("There isn't an \"w\" letter in", name)

################################################################################

for letter in name :
    print(letter)

################################################################################

l: int = len(name)

for i in range(0, l) :
    print(name[i])

################################################################################

for i in range(0, -l, -1) :
    print(name[i])

################################################################################

# for i in range(0, l) :
#     name[i] = name[0] # error: TypeError: 'str' object does not support item assignment

################################################################################

start  : int = 2
finish : int = len(name) - 2

print(name[start:finish])

print(name[0:finish])
print(name[:finish])

print(name[start:])

print(name[:])

################################################################################
