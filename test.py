def fib(n):
    #print("== N ==")
    #print(str(n))
    if n < 2:
        #print("== RET ==")
        #print(str(n))
        return n
    #print("== CALLER1 ==")
    #print(n - 2)
    #print("== CALLER2 ==")
    #print(n - 1)
    res = fib(n - 2) + fib(n - 1)
    #print("== RES ==")
    #print(str(res))
    return res
print(fib(30))