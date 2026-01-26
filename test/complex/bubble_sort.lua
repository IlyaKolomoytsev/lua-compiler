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

local a = {}
print "input size"
local size = io.read()
for i = 1, tonumber(size) do
    print("input value with index", i)
    local val = io.read()
    a[i] = tonumber(val);
end

bubbleSort(a)

print "\nsorted array:"
for i = 1, #a do
    print(a[i])
end