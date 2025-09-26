-- Тест логических операторов в Lua

local a = true
local b = false

-- оператор И
local result_and = a and b

-- оператор ИЛИ
local result_or = a or b

-- оператор НЕ
local result_not_a = not a
local result_not_b = not b

-- комбинации
local complex = (a and not b) or (not a and b)

-- проверка внутри условия
if a and (b or not b) then
    print("Condition is fulfilled")
else
    print("Condition isn`t fulfilled")
end