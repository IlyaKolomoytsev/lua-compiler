-- Проверка операторов присваивания и сравнения

local a = 10        -- оператор =
local b = 20

-- Сравнения
if a == b then
print("a равно b")
end

if a ~= b then       -- оператор ~= (не равно)
print("a не равно b")
end

if a < b then        -- оператор <
print("a меньше b")
end

if a <= b then       -- оператор <=
print("a меньше или равно b")
end

if a > b then        -- оператор >
print("a больше b")
end

if a >= b then       -- оператор >=
print("a больше или равно b")
end

-- Проверка, что лексер не путает точку и конкатенацию
local s = "Hello" .. " World"   -- оператор ..

-- И что лексер не путает '...' (varargs) с '..'
local function f(...) print(...) end