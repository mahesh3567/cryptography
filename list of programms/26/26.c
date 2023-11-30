#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
	int x;
    for (x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

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
    *e = 17;
    *d = modInverse(*e, phi);
}

int rsaEncrypt(int plaintext, int e, int n) {
    return modExp(plaintext, e, n);
}

int rsaDecrypt(int ciphertext, int d, int n) {
    return modExp(ciphertext, d, n);
}

int main() {
    int n, e, d;
    generateKeys(&n, &e, &d);

    int plaintext = 42;
    printf("Original plaintext: %d\n", plaintext);

    int ciphertext = rsaEncrypt(plaintext, e, n);
    printf("Encrypted ciphertext: %d\n", ciphertext);

    printf("Leaked private key: %d\n", d);

    generateKeys(&n, &e, &d);

    int decryptedText = rsaDecrypt(ciphertext, d, n);
    printf("Decrypted text with leaked private key: %d\n", decryptedText);

    return 0;
}

