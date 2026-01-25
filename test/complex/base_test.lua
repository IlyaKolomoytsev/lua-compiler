function factorial(n)
    if n <= 1 then
        return 1
    end
    return n * factorial(n - 1)
end

print("factorial(20) =", factorial(20))  -- 2432902008176640000

function bubbleSort(arr)
    local n = #arr
    for i = 1, n - 1 do
        for j = 1, n - i do
            if arr[j] > arr[j + 1] then
                local tmp = arr[j]
                arr[j] = arr[j + 1]
                arr[j + 1] = tmp
            end
        end
    end
end

numbers = {5, 2, 9, 1, 3}

print("before sort:")
for i = 1, #numbers do
    print(numbers[i])
end

bubbleSort(numbers)

print("after sort:")
for i = 1, #numbers do
    print(numbers[i])
end

person = {
    name = "Alice",
    age = 20
}

print("name =", person.name)
print("age =", person.age)

person.age = person.age + 1
print("age after birthday =", person.age)

Vector = {}
Vector.__index = Vector

function Vector:new(x, y)
    local obj = { x = x, y = y }
    setmetatable(obj, Vector)
    return obj
end

Vector.__add = function(a, b)
    return Vector:new(a.x + b.x, a.y + b.y)
end

v1 = Vector:new(2, 3)
v2 = Vector:new(4, 5)
v3 = v1 + v2

print("v3.x =", v3.x)  -- 6
print("v3.y =", v3.y)  -- 8

i = 1
sum = 0

while i <= 10 do
    sum = sum + i
    i = i + 1
end

print("sum 1..10 =", sum)  -- 55