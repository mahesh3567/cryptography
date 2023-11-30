#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int e, int f_n) {
    int m0 = f_n, t, q;
    int x0 = 0, x1 = 1;

    if (f_n == 1)
        return 0;

    while (e > 1) {
        q = e / f_n;

        t = f_n;
        f_n = e % f_n, e = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q,i;
    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }
    int f_n = (p - 1) * (q - 1);
    int d = modInverse(e, f_n);
    printf("Private Key (d): %d\n", d);

    return 0;
}

