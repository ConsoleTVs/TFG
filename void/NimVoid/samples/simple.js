var a = 0;
var b = 0;

while (a < 3000000) {
    b = a - b / 2;
    a = a + 1;
}
console.log(b);