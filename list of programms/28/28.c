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
int diffieHellman(int x, int a, int q) {
    return modExp(a, x, q);
}

int main() {
    int q = 23;  
    int a = 5; 
    int secretAlice = 6;
    int secretBob = 15;
    int publicAlice = diffieHellman(secretAlice, a, q);
    int publicBob = diffieHellman(secretBob, a, q);
    int sharedSecretAlice = diffieHellman(secretAlice, publicBob, q);
    int sharedSecretBob = diffieHellman(secretBob, publicAlice, q);
    printf("Public values exchanged:\n");
    printf("Alice sends to Bob: %d\n", publicAlice);
    printf("Bob sends to Alice: %d\n", publicBob);

    printf("\nShared secret calculated by both Alice and Bob:\n");
    printf("Alice's shared secret: %d\n", sharedSecretAlice);
    printf("Bob's shared secret: %d\n", sharedSecretBob);

    return 0;
}

