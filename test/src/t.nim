type
    A = ref object
        i: B
    B = ref object
        i: A

var
    a: A = new A
    b: B = new B
a.i = b
echo "OK"