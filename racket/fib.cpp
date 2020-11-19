// Source: https://satosystems.hatenablog.com/entry/20121228/1356655565
#include <stdio.h>

int fib(int n) {
    if (n < 2) return n;
    return fib(n - 2) + fib(n - 1);
}

int main(int argc, char *argv[]) {
    printf("%d\n", fib(45));
    return 0;
}
