a = { v = 7 }
b = { v = 2 }

mt = {
    __idiv = function(x, y)
        return { v = x.v // y.v }
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

c = a // b
print(c.v)  -- ожидается: 3