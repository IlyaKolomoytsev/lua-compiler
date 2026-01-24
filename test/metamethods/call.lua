t = {}
mt = {
    __call = function(tbl, x, y)
        return x + y
    end
}

setmetatable(t, mt)

print(t(2, 3))  -- 5