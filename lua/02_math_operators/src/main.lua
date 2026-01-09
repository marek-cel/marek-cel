print("Math Operations in Lua")
print()

--------------------------------------------------------------------------------

local a = 4
local b = 2

-- Addition
local sum = a + b
print("Addition:")
print(a .. " + " .. b .. " = " .. sum)
print()

-- Subtraction
local difference = a - b
print("Subtraction:")
print(a .. " - " .. b .. " = " .. difference)
print()

-- Multiplication
local product = a * b
print("Multiplication:")
print(a .. " * " .. b .. " = " .. product)
print()

-- Division
local quotient = a / b
print("Division:")
print(a .. " / " .. b .. " = " .. quotient)
print()

-- Modulus
local remainder = a % b
print("Modulus:")
print(a .. " % " .. b .. " = " .. remainder)
print()

-- Exponentiation
local power = a ^ b
print("Exponentiation:")
print(a .. " ^ " .. b .. " = " .. power)
print()

-- square root
local square_root = math.sqrt(a)
print("Square Root:")
print("sqrt(" .. a .. ") = " .. square_root)
print()

-- floor
local rounded = math.floor(a + 0.5)
print("Floor:")
print("round(" .. (a + 0.5) .. ") = " .. rounded)
print()

-- ceil
local ceiling = math.ceil(a + 0.5)
print("Ceil:")
print("ceil(" .. (a + 0.5) .. ") = " .. ceiling)
print()

-- absolute value
local absolute = math.abs(-a)
print("Absolute Value:")
print("abs(" .. -a .. ") = " .. absolute)
print()

-- min
local minimum = math.min(a, b)
print("Minimum:")
print("min(" .. a .. ", " .. b .. ") = " .. minimum)
print()

-- max
local maximum = math.max(a, b)
print("Maximum:")
print("max(" .. a .. ", " .. b .. ") = " .. maximum)
print()

-- random number
local random_number = math.random(1, 10)
print("Random Number:")
print("random(1, 10) = " .. random_number)
print()

-- sine
local sine_value = math.sin(math.pi / 2)
print("Sine:")
print("sin(pi/2) = " .. sine_value)
print()

-- cosine
local cosine_value = math.cos(math.pi / 2)
print("Cosine:")
print("cos(pi/2) = " .. cosine_value)
print()

--------------------------------------------------------------------------------

print("End of Math Operations")

