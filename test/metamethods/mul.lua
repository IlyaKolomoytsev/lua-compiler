a = { v = 3 }
b = { v = 4 }

mt = {
    __mul = function(lhs, rhs)
        return { v = lhs.v * rhs.v }
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

c = a * b
print(c.v)  -- ожидается: 12