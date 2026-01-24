a = { v = 10 }
b = { v = 10 }

mt = {
    __eq = function(x, y)
        return x.v == y.v
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

print(a == b)  -- ожидается: true