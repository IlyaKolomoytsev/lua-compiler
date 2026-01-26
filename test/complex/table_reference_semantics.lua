obj = { name = "Lua" }
arr = { 10, 20, 30 }
num = 5
str = "hello"

f = function(n, s, a, o)
    print("inside start:", n, s, a[1], o.name)

    n = 100
    s = "world"

    a[1] = 999
    o.name = "Changed"

    a = { 1, 2, 3 }
    o = { name = "NewObj" }

    print("inside end:", n, s, a[1], o.name)
end

f(num, str, arr, obj)

print("outside:", num, str, arr[1], obj.name)