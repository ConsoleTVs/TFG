a = 5
def test():
    global a
    a = 10
test()
print(a)