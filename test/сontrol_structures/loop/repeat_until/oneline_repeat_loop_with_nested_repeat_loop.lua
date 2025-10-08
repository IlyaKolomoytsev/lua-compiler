local i = 1
repeat print("Outer loop i =", i) local j = 1 repeat print("  Inner loop j =", j) j = j + 1 until j > 2 i = i + 1 until i > 3