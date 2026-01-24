function div(a, b)
    if b == 0 then
        error("division by zero")
    end
    return a / b
end

print(pcall(div, 10, 2))
print(pcall(div, 10, 0))