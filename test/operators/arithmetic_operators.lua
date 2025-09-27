-- Проверка арифметических операторов в Lua

local a = 15
local b = 4

-- сложение
local sum = a + b        -- 19

-- вычитание
local diff = a - b       -- 11

-- умножение
local prod = a * b       -- 60

-- деление (всегда float)
local div = a / b        -- 3.75

-- целочисленное деление
local int_div = a // b   -- 3

-- остаток от деления
local mod = a % b        -- 3

-- возведение в степень
local pow = a ^ b        -- 15^4 = 50625

-- унарный минус
local neg = -a           -- -15

-- проверка в print
print("sum =", sum)
print("diff =", diff)
print("prod =", prod)
print("div =", div)
print("int_div =", int_div)
print("mod =", mod)
print("pow =", pow)
print("neg =", neg)
