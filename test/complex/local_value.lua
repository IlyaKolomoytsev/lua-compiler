function createCounter()
    local value = 0  -- приватное поле

    return {
        inc = function()
            value = value + 1
        end,
        get = function()
            return value
        end
    }
end

c = createCounter()
c.inc()
print(c.get())  -- 1
print(c.value)  -- nil