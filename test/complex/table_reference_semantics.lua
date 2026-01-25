table = {};
f = function (p) -- Передаем копию ссылки на объект
    p.field = 1 -- Меняем внутреннее состояние объекта
    print("param =", p)
    p = 2; -- Внешний объект не перезаписывается
    print("param =", p)
end

f(table)
print("table =", table)
print("field =", table.field)