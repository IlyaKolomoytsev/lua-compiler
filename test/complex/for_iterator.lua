function range(start, finish, step)
    local function iter(state, current)
        if current == nil then
            current = state.start
        else
            current = current + state.step
        end

        if (state.step >= 0 and current <= state.finish) or (state.step < 0 and current >= state.finish)
        then
            return current
        end

        return nil
    end

    local state = { start = start, finish = finish, step = step }
    return iter, state, nil
end

for i in range(0, 10, 2.5) do
    print(i)
end
