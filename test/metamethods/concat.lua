a = { v = "Hello, " }
b = { v = "world" }

mt = {
    __concat = function(x, y)
        return { v = x.v .. y.v }
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

c = a .. b
print(c.v)  -- ожидается: Hello, world