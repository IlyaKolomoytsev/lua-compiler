a = { v = 20 }
b = { v = 6 }

mt = {
    __mod = function(lhs, rhs)
        return { v = lhs.v % rhs.v }
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

c = a % b
print(c.v)  -- ожидается: 2