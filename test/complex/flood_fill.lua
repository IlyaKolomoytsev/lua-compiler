-- 0 — пусто
-- 1 — стена
-- 2 — заливка

field = {
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1}
}

function fill(x, y)
    if field[y][x] ~= 0 then
        return
    end

    field[y][x] = 2

    fill(x+1, y)
    fill(x-1, y)
    fill(x, y+1)
    fill(x, y-1)
end

fill(3, 3)

for y = 1, #field do
    print(
            field[y][1],
            field[y][2],
            field[y][3],
            field[y][4],
            field[y][5]
    )
end