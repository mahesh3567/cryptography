#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
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
int rsaEncrypt(int plaintext, int e, int n) {
    return modExp(plaintext, e, n);
}

int main() {
    int e = 65537;
    int n = 2537;
	int i; 
    int plaintext = 42; 
    if (gcd(plaintext, n) > 1) {
        printf("Plaintext has a common factor with n. Breaking the RSA encryption...\n");
        for (i = 2; i <= n; ++i) {
            if (n % i == 0) {
                printf("Found a factor: %d\n", i);
                break;
            }
        }
    } else {
        int ciphertext = rsaEncrypt(plaintext, e, n);
        printf("Encrypted ciphertext: %d\n", ciphertext);
    }

    return 0;
}

