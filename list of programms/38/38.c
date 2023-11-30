#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int modInverse(int a, int m) {
    a = a % m;
    int x;
    for ( x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
void encryptHill(const char *plaintext, const int key[2][2], char *ciphertext) {
    size_t text_len = strlen(plaintext);
    size_t padded_len = (text_len % 2 == 0) ? text_len : text_len + 1;
    char *padded_text = malloc(padded_len + 1); 
    strcpy(padded_text, plaintext);
    if (text_len % 2 != 0) {
        padded_text[text_len] = 'X';
        padded_text[text_len + 1] = '\0';
    }

    int i;
    for (i = 0; i < padded_len; i += 2) {
        int p1 = padded_text[i] - 'A';
        int p2 = padded_text[i + 1] - 'A';

        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;

        ciphertext[i] = c1 + 'A';
        ciphertext[i + 1] = c2 + 'A';
    }

    ciphertext[padded_len] = '\0'; 
    free(padded_text);
}
void decryptHill(const char *ciphertext, const int key[2][2], char *decryptedtext) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;

    int keyInverse[2][2];
    keyInverse[0][0] = key[1][1];
    keyInverse[0][1] = -key[0][1];
    keyInverse[1][0] = -key[1][0];
    keyInverse[1][1] = key[0][0];
    int detInverse = modInverse(det, 26);

    int i,j;
    for ( i = 0; i < 2; ++i) {
        for ( j = 0; j < 2; ++j) {
            keyInverse[i][j] = (keyInverse[i][j] + 26) % 26;
        }
    }
    for (i = 0; i < 2; ++i) {
        for ( j = 0; j < 2; ++j) {
            keyInverse[i][j] = (keyInverse[i][j] * detInverse) % 26;
        }
    }

    size_t text_len = strlen(ciphertext);
    for (i = 0; i < text_len; i += 2) {
        int c1 = ciphertext[i] - 'A';
        int c2 = ciphertext[i + 1] - 'A';

        int p1 = (keyInverse[0][0] * c1 + keyInverse[0][1] * c2) % 26;
        int p2 = (keyInverse[1][0] * c1 + keyInverse[1][1] * c2) % 26;

        decryptedtext[i] = (p1 + 26) % 26 + 'A';
        decryptedtext[i + 1] = (p2 + 26) % 26 + 'A';
    }

    decryptedtext[text_len] = '\0';
}

int main() {
    const char *plaintext = "HELLO";
    char ciphertext[10];
    char decryptedtext[10];

    int key[2][2] = {{6, 24}, {1, 13}};
    encryptHill(plaintext, key, ciphertext);
    printf("Plaintext:   %s\n", plaintext);
    printf("Ciphertext:  %s\n", ciphertext);
    printf("\nKnown-Plaintext Attack:\n");
    const char *knownPlaintext = "WORLD";
    char knownCiphertext[10];

    encryptHill(knownPlaintext, key, knownCiphertext);
    printf("Known Ciphertext: %s\n", knownCiphertext);
    key[0][0] = (knownPlaintext[0] - 'A' + 26) % 26;
    key[0][1] = (knownPlaintext[1] - 'A' + 26) % 26;
    key[1][0] = (knownPlaintext[2] - 'A' + 26) % 26;
    key[1][1] = (knownPlaintext[3] - 'A' + 26) % 26;

    decryptHill(ciphertext, key, decryptedtext);
    printf("Recovered Key: [%d %d %d %d]\n", key[0][0], key[0][1], key[1][0], key[1][1]);
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}

