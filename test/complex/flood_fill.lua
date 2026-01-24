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