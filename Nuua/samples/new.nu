number = 0

if (number > 10) ->> print -> (number + " is lower than 10")
if (number > 10) {
    print -> (number + " is lower than 10 (2)")
}

while (number > 20) ->> number = number + 1
while (number > 30) {
    number = number + 1
}

add = (a, b) -> a + b
add2 = (a, b) ->> return a + b
add3 = (a, b) {
    return a + b
}

print -> (add -> (1, 1))
print -> (add2 -> (1, 1))
print -> (add3 -> (1, 1))

p = Persona()
p.age()
p.age = () => ..