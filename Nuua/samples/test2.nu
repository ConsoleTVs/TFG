test = (n) {
    if (n == 0) {
        return
    }
    return f(n - 1)
}

test(100)