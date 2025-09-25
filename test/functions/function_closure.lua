function counter()
    local count = 0
    function fn()
        count = count + 1
        return count
    end
    return fn
end