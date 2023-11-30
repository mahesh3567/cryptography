#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void generateKeys(int *n, int *e, int *d) {
    int p = 61;
    int q = 53;
    *n = p * q;
    int phi = (p - 1) * (q - 1);
    *e = 65537; 
    *d = modExp(*e, -1, phi);
}

int rsaEncrypt(int plaintext, int e, int n) {
    return modExp(plaintext, e, n);
}

int rsaDecrypt(int ciphertext, int d, int n) {
    return modExp(ciphertext, d, n);
}

int main() {
    int n,i, e, d;
    generateKeys(&n, &e, &d);

    char message[] = "HELLO";
    int len = sizeof(message) - 1;

    printf("Original message: %s\n", message);

    printf("Encrypted message: ");
    for (i = 0; i < len; ++i) {
        int plaintext = message[i] - 'A';
        int ciphertext = rsaEncrypt(plaintext, e, n);
        printf("%d ", ciphertext);
    }
    printf("\n");

    printf("Bob's private key (d): %d\n", d);

    return 0;
}

