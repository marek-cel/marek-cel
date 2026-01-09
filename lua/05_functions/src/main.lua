print("Functions")
print()

--------------------------------------------------------------------------------

local function foo()
  print("foo called")
  print()
end

foo()

-- functions with parameters

local function add(a, b)
  return a + b
end

local sum = add(3, 5)
print("Sum:", sum)
print()

-- functions with multiple return values
local function swap(x, y)
  return y, x
end

local a, b = swap(10, 20)
print("Swapped:", a, b)

