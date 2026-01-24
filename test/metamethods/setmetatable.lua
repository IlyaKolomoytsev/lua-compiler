t = {}
mt = { __index = { x = 42 } }

setmetatable(t, mt)

print(t.x)   -- 42