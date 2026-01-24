a = { v = 3 }
b = { v = 5 }

mt = {
    __le = function(x, y)
        return x.v <= y.v
    end
}

setmetatable(a, mt)
setmetatable(b, mt)

print(a <= b)  -- true