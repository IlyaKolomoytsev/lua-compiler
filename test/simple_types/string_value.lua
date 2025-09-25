baseString = string()
emptyStringDoubleQuotes = ""
emptyStringSingleQuotes = ''
space = ' '
letters = "abcdefghigklmnopqrstuvwxyz"
slavicLetters = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
numbers = "0123456789"
specialSymbols = "!@#$%^&*()№;:?/~`|{}<>_-+=.,"
controlStructures = "\a\b\f\n\r\t\v\0\"\'\\"
controlStructuresSingleQuotes = '\''
symbolByHexCode = "\x48\x49 number №\x301"
symbolByDecCode = "\72\073 number №\0481"
unicodeSymbols = "Тест с юникодом 🚀🌍"
unicodeSymbolByCode = "\u{1F600}"
multiLineInOneLine = [[Hello world!]]
multiLineWithEscapes = [[
This is a multi-line string
with an escaped quote: \" and backslash: \\
]]
multiLineWithQuotes = [[
This string contains "double quotes" and 'single quotes'.
]]
multiLineWithEmptyLines = [[
This is a line.

This is another line with a blank line above it.
]]
multiLineWithEscapedNewLine = [[
This is a line.\n
This is another line.
]]
multiLineWithComment = [[
This is a multi-line string.
-- This is a comment inside the string
]]
level1 = [=[This is a multi-line string with level 1.]=]
level2 = [==[This is a multi-line string with level 2.]==]
level3 = [===[
This is a multi-line string with level 3.
It can contain [[ and ]] without causing problems.
]===]
nestedLevels = [==[This string contains a nested level:
[===[
Nested string inside level 3.
]===]
Continuing with outer string.]==]