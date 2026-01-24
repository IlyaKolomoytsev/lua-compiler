a = { v = 7 }

mt = {
    __unm = function(x)
        return { v = -x.v }
    end
}

setmetatable(a, mt)

b = -a
print(b.v)  -- ожидается: -7