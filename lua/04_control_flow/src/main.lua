print("Control Flow Statements in Lua")
print()

--------------------------------------------------------------------------------

-- If-Else Statement
local number = 10
if number > 0 then
    print(number .. " is a positive number.")
elseif number < 0 then
    print(number .. " is a negative number.")
else
    print(number .. " is zero.")
end
print()

-- While Loop
local count = 1
while count <= 5 do
    print("Count is: " .. count)
    count = count + 1
end
print()

-- Repeat-Until Loop
local repeatCount = 1
repeat
    print("Repeat Count is: " .. repeatCount)
    repeatCount = repeatCount + 1
until repeatCount > 5
print()

-- For Loop
for i = 1, 5 do
    print("For Loop iteration: " .. i)
end
print()

