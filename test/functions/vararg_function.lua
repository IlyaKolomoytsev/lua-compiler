function printAll(...)
    for i, v in ipairs({...}) do
        print(i, v)
    end
end