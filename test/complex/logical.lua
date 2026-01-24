print("=== Boolean literals ===")
print(true)
print(false)
print(not true)     -- false
print(not false)    -- true

print("=== Comparisons ===")
print(1 == 1)       -- true
print(1 ~= 2)       -- true
print(2 < 3)        -- true
print(3 <= 3)       -- true
print(5 > 2)        -- true
print(5 >= 6)       -- false

print("=== and / or basic ===")
print(true and true)    -- true
print(true and false)   -- false
print(false or true)    -- true
print(false or false)   -- false

print("=== Short-circuit tests ===")
print(false and (1 / 0))    -- false (правая часть НЕ вычисляется)
print(true or (1 / 0))      -- true  (правая часть НЕ вычисляется)

print("=== Truthy / Falsy ===")
print(0 and 1)          -- 1
print(0 or 1)           -- 0
print(nil or 5)         -- 5
print(nil and 5)        -- nil
print("hello" and 123)  -- 123
print("" or 42)         -- "" (пустая строка — truthy!)

print("=== not operator ===")
print(not 0)            -- false
print(not nil)          -- true
print(not "")           -- false

print("=== Complex logical expressions ===")
print((5 > 3) and (2 < 4))                 -- true
print((5 > 3) and (2 > 4))                 -- false
print((5 < 3) or (2 < 4))                  -- true
print(not ((5 < 3) or false))              -- true

print("=== Logic + math ===")
print((10 % 2 == 0) and (5 * 2 == 10))     -- true
print((2 ^ 3 == 8) or (1 / 0))             -- true (short-circuit)