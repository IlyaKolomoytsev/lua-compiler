a = { v = {1, 2, 3, 4} }

mt = {
    __len = function(x)
        return #x.v
    end
}

setmetatable(a, mt)

print(#a)  -- ожидается: 4