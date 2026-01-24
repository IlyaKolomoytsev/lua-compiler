print("=== BRANCHING TESTS START ===")

-- A) Простое if / else
print("\n-- A) simple if/else")

if true then
    print("A1: OK (true branch)")
else
    print("A1: FAIL")
end

if false then
    print("A2: FAIL")
else
    print("A2: OK (false branch)")
end


-- B) Lua truthiness
print("\n-- B) truthiness")

if nil then
    print("B1: FAIL (nil is false)")
else
    print("B1: OK (nil)")
end

if false then
    print("B2: FAIL (false is false)")
else
    print("B2: OK (false)")
end

if 0 then
    print("B3: OK (0 is truthy)")
else
    print("B3: FAIL")
end

if "" then
    print("B4: OK (empty string is truthy)")
else
    print("B4: FAIL")
end


-- C) elseif chain
print("\n-- C) elseif chain")

local x = 2
if x == 1 then
    print("C: FAIL (x == 1)")
elseif x == 2 then
    print("C: OK (x == 2)")
elseif x == 3 then
    print("C: FAIL (x == 3)")
else
    print("C: FAIL (else)")
end


-- D) only one branch must execute
print("\n-- D) only one branch")

local y = 1
if y == 1 then
    print("D1: OK")
elseif y == 1 then
    print("D2: FAIL (elseif should not run)")
else
    print("D3: FAIL")
end


-- E) nested if
print("\n-- E) nested if")

local z = 1
if z == 1 then
    if false then
        print("E1: FAIL")
    else
        print("E2: OK (nested else)")
    end
else
    print("E3: FAIL")
end


-- F) logical operators
print("\n-- F) logical operators")

if true and true then
    print("F1: OK (true and true)")
else
    print("F1: FAIL")
end

if true and false then
    print("F2: FAIL")
else
    print("F2: OK (true and false)")
end

if false or true then
    print("F3: OK (false or true)")
else
    print("F3: FAIL")
end

if false or false then
    print("F4: FAIL")
else
    print("F4: OK (false or false)")
end


-- G) not operator
print("\n-- G) not operator")

if not true then
    print("G1: FAIL")
else
    print("G1: OK (not true)")
end

if not false then
    print("G2: OK (not false)")
else
    print("G2: FAIL")
end

if not nil then
    print("G3: OK (not nil)")
else
    print("G3: FAIL")
end


print("\n=== BRANCHING TESTS END ===")