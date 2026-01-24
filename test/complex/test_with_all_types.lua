-- types_ops_test.lua

print("nil:", nil)

-- boolean
print("bool:", true and false, true or false, not false)         -- false  true  true
print("bool cmp:", (true == true), (false ~= true))              -- true   true

-- number (integer/float)
print("num arith:", 5 + 2, 5 - 2, 5 * 2, 5 / 2)                  -- 7 3 10 2.5
print("num extra:", 5 % 2, 5 ^ 2, 5 // 2, -5)                    -- 1 25 2 -5
print("num cmp:", 5 < 6, 5 <= 5, 7 > 3, 7 >= 7, 5 == 5)          -- true true true true true

-- string
print("str:", "he" .. "llo")                                     -- hello
print("str cmp:", ("a" < "b"), ("ab" <= "ab"), ("x" ~= "y"))      -- true true true
print("str len:", #"hello")                                      -- 5

-- table
t = {1, 2, 3, a = 10, b = "ok"}
print("table idx:", t[1], t[2], t.a, t["b"])                     -- 1 2 10 ok
t[1] = 99
t.c = 42
print("table set:", t[1], t.c)                                   -- 99 42
print("table len:", #t)                                          -- (зависит от массива-части; тут обычно 3)

-- function
f = function(x, y) return x + y end
print("function call:", f(2, 3))                                 -- 5
