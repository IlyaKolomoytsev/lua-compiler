a = { x = 2 }
b = { x = 3 }

mt = {
    __add = function(lhs, rhs)
        return { x = lhs.x + rhs.x }
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

c = a + b
print(c.x) -- ожидается: 5