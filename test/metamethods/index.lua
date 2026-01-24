a = {}
mt = {
    __index = {
        x = 42
    }
}

setmetatable(a, mt)

print(a.x)  -- 42