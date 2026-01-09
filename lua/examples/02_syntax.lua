-- this is a comment

--[[
    this is a
    multi-line comment
--]]

--------------------------------------------------------------------------------

local number = 1

local string = "hello, world"
local single = 'hello, world'
local multiline = [[
    hello,
    world
]]

local truth, lies = true, false

local nothing = nil

-- indexing starts at 1 !!!
local table = {1, "hello", false}

-- append to a table
table[4] = 3.14

for i = 1, 4 do
    print("table[" .. i .. "] = " .. tostring(table[i]))
end

local map = {
    ["hello"] = "world",
    ["foo"] = "bar",
    ["baz"] = "qux"
}

--------------------------------------------------------------------------------

print(number)
print(string)
print(single)
print(multiline)
print(truth)
print(lies)
print(nothing)
print(table[1])
print(table[2])
print(table[3])
print(map["hello"])
print(map["foo"])
print(map["baz"])

--------------------------------------------------------------------------------

print() -- prints an empty line

local function print_hello()
    print("hello, functions")
end

print_hello()

local function add(a, b)
    return a + b
end

local function multiple_returns()
    return 11, 22
end

local result = add(1, 2)
print(result)

local a, b = multiple_returns()
print(a)
print(b)

--------------------------------------------------------------------------------

print() -- prints an empty line

if number == 1 then
    print("number is 1")
elseif number == 2 then
    print("number is 2")
else
    print("number is something else")
end

--------------------------------------------------------------------------------

print() -- prints an empty line

for i = 1, 3 do
    print(i)
end

--------------------------------------------------------------------------------

print() -- prints an empty line

while number < 5 do
    print(number)
    number = number + 1
end
print("number is now ", number)

