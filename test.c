#include <stdio.h>

int main()
{
    int i, res = 0.0;
    while (i < 10000) {
        res = res + i * 2;
        i = i + 1;
    }
}