local function hi(a, s)
    local str = "func_print: " .. s
    print(str)
    return a
end

-- читаем число
local line = io.read("*l")
local number = tonumber(line)

-- не ввели число
if number == nil then
    print "input string is not number"
    return
end

if number > 10 and hi(true, "number > 10 && hi(true)") then
    print("branch_print: number > 10 && hi(true)")
    print("")
end

if number > 5 and hi(true, "number > 5 && hi(true)") then
    print("branch_print: number > 5 && hi(true)")
    print("")
end

if number > 10 or hi(true, "number > 10 || hi(true)") then
    print("branch_print: number > 10 || hi(true)")
    print("")
end

if number > 5 or hi(true, "number > 5 || hi(true)") then
    print("branch_print: number > 5 || hi(true)")
    print("")
end

if number > 10 and hi(false, "number > 10 && hi(false)") then
    print("branch_print: number > 10 && hi(false)")
    print("")
end

if number > 5 and hi(false, "number > 5 && hi(false)") then
    print("branch_print: number > 5 && hi(false)")
    print("")
end

if number > 10 or hi(false, "number > 10 || hi(false)") then
    print("branch_print: number > 10 || hi(false)")
    print("")
end

if number > 5 or hi(false, "number > 5 || hi(false)") then
    print("branch_print: number > 5 || hi(false)")
    print("")
end
