local i = 1
while i <= 3 do
    print("Outer loop, i = " .. i)

    local j = 1
    while j <= 2 do
        print("  Inner loop, j = " .. j)
        j = j + 1
    end

    i = i + 1
end