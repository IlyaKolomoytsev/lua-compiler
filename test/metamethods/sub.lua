a = { x = 10 }
b = { x = 4 }

mt = {
    __sub = function(lhs, rhs)
        return { x = lhs.x - rhs.x }
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

c = a - b
print(c.x) -- ожидается: 6