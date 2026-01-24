a = {}
mt = {
    __newindex = function(t, k, v)
        rawset(t, k, v * 2)
    end
}

setmetatable(a, mt)

a.x = 10
print(a.x)  -- 20