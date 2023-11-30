#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int areCoprime(int a, int b) {
    return gcd(a, b) == 1;
}

int main() {
    int a, b;
    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("Enter the value of b: ");
    scanf("%d", &b);
    if (areCoprime(a, 26) && areCoprime(b, 26) && (a % 2 != 0 || a == 2)) {
        printf("Valid values of a and b for the affine Caesar cipher.\n");
    } else {
        printf("Invalid values of a and/or b for the affine Caesar cipher.\n");
    }

    return 0;
}

