print("Boolean Operations in Lua")
print()

--------------------------------------------------------------------------------

local truth = true
local lies = false
local result = nil

-- Logical AND
result = truth and lies
print("true and false =", result)  -- Expected: false

-- Logical OR
result = truth or lies
print("true or false =", result)   -- Expected: true

-- Logical NOT
result = not truth
print("not true =", result)         -- Expected: false

--------------------------------------------------------------------------------

print("End of Boolean Operations")

