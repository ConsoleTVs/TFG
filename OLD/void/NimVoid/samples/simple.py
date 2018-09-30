a = 0.0
b = 0.0

while a < 6000000.0:
    b = a - b / 2
    a = a + 1

print(b)