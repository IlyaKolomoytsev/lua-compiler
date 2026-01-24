a = { v = 2 }
b = { v = 5 }

mt = {
    __pow = function(lhs, rhs)
        return { v = lhs.v ^ rhs.v }
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

c = a ^ b
print(c.v)  -- ожидается: 32