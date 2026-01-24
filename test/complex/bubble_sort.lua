function bubbleSort(arr)
    local n = #arr
    for i = 1, n - 1 do
        for j = 1, n - i do
            if arr[j] > arr[j + 1] then
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
            end
        end
    end
end

local a = {5, 1, 4, 2, 8}

bubbleSort(a)

for i = 1, #a do
    print(a[i])
end