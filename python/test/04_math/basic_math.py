#!/usr/bin/env python3

################################################################################

import math

################################################################################

var1 = int(input("Enter 1st value "))
var2 = int(input("Enter 2nd value "))

print()

print("         Sum: ", var1 + var2) 
print("  Difference: ", var1 - var2) 
print("     Product: ", var1 * var2) 
print("    Quotient: ", var1 / var2) 
print("Int Quotient: ", var1 // var2)
print("      Modulo: ", var1 % var2) 
print("       Power: ", var1 ** var2)

print()

print("     Minimum: ", min(5, 10, 25))
print("     Maximum: ", max(5, 10, 25))
print("Absolute val: ", abs(-7.25))
print("       Power: ", pow(var1, var2))

print()
  
print("Square root: ", math.sqrt(var1))
print("Expotential: ", math.exp(var1)) 

print()

print("Ceil: ", math.ceil(3.14)) 
print("Floor: ", math.floor(3.14)) 

print()

print("pi: ", math.pi)
print("degrees(pi): ", math.degrees(math.pi))
print("radians(90): ", math.radians(90))

print()

print("cos(pi): ", math.cos(math.pi)) 
print("sin(pi): ", math.sin(math.pi)) 
print("tan(pi): ", math.tan(math.pi))

print()

print("atan2(1,2): ", math.atan2(1,2))

print()

print("gcd(6,9): ", math.gcd(6,9)) # greatest common divisor

print()

print("dist((0,0),(1,1)): ", math.dist((0,0),(1,1))) # Euclidean distance between two points

################################################################################
