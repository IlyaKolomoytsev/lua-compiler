a = {}
mt = {
    __index = function()
        return 52
    end
}

setmetatable(a, mt)

print(a.x)  -- 52