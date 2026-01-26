-- Sizes
local n, m = 10, 10

-- Matrix (0/1 как числа)
local matrix = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
}

-- Read start position (x, y) and the new fill value, each on its own line
-- xLua = x + 1, yLua = y + 1
local x = tonumber(io.read())  -- start row index (0-based)
local y = tonumber(io.read())  -- start column index (0-based)
local newColorLine = io.read() -- e.g., "2"
local newColor = tonumber(newColorLine) or newColorLine

local xLua, yLua = x + 1, y + 1

-- Recursive flood fill:
-- Replaces all connected cells (4-directionally) that match oldColor with newColor.
local function floodFill(mat, i, j, oldColor, newColor, n, m)
    -- 1) Stop if out of bounds (Lua: 1..n, 1..m)
    if i < 1 or i > n or j < 1 or j > m then
        return
    end

    -- 2) Stop if this cell is NOT the target color
    if mat[i][j] ~= oldColor then
        return
    end

    -- 3) Fill current cell
    mat[i][j] = newColor

    -- 4) Recurse to 4 neighbors
    floodFill(mat, i + 1, j, oldColor, newColor, n, m) -- down
    floodFill(mat, i - 1, j, oldColor, newColor, n, m) -- up
    floodFill(mat, i, j + 1, oldColor, newColor, n, m) -- right
    floodFill(mat, i, j - 1, oldColor, newColor, n, m) -- left
end

-- Remember the color at the starting cell
local oldColor = matrix[xLua][yLua]

-- Only run fill if oldColor differs from newColor
if oldColor ~= newColor then
    floodFill(matrix, xLua, yLua, oldColor, newColor, n, m)
end

-- Output final matrix
for y = 1, #matrix do
    print(
            matrix[y][1],
            matrix[y][2],
            matrix[y][3],
            matrix[y][4],
            matrix[y][5],
            matrix[y][6],
            matrix[y][7],
            matrix[y][8],
            matrix[y][9],
            matrix[y][10]
    )
end