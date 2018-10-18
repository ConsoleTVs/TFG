a = 0
b = 0
unroll (12000000, 2) {
    b = b + 1
    a = a + 1
}
b