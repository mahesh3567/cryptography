#include <stdio.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    int x;
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
char encrypt(char plaintext, int a, int b) {
    if (isalpha(plaintext)) {
        char base = isupper(plaintext) ? 'A' : 'a';
        return ((a * (plaintext - base) + b) % 26) + base;
    } else {
        return plaintext; 
    }
}

char decrypt(char ciphertext, int a, int b) {
    int a_inverse = modInverse(a, 26);
    if (a_inverse == -1) {
        fprintf(stderr, "Error: Modular inverse does not exist.\n");
        return '\0';
    }

    if (isalpha(ciphertext)) {
        char base = isupper(ciphertext) ? 'A' : 'a';
        return ((a_inverse * (ciphertext - base - b + 26)) % 26) + base;
    } else {
        return ciphertext; 
    }
}

void encryptAffineCaesar(const char *plaintext, int a, int b, char *ciphertext) {
    size_t text_len = strlen(plaintext);
    int i;
    for ( i = 0; i < text_len; ++i) {
        ciphertext[i] = encrypt(plaintext[i], a, b);
    }

    ciphertext[text_len] = '\0'; 
}

void decryptAffineCaesar(const char *ciphertext, int a, int b, char *decryptedtext) {
    size_t text_len = strlen(ciphertext);
    int i;
    for ( i = 0; i < text_len; ++i) {
        decryptedtext[i] = decrypt(ciphertext[i], a, b);
    }

    decryptedtext[text_len] = '\0'; 
}

int main() {
    const char *plaintext = "HelloWorld";
    int a = 3; 
    int b = 5;

    size_t text_len = strlen(plaintext);
    char *ciphertext = malloc(text_len + 1); 
    char *decryptedtext = malloc(text_len + 1);

    if (ciphertext == NULL || decryptedtext == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;
    }

    encryptAffineCaesar(plaintext, a, b, ciphertext);
    printf("Plaintext:      %s\n", plaintext);
    printf("Encryption (a=%d, b=%d): %s\n", a, b, ciphertext);

    decryptAffineCaesar(ciphertext, a, b, decryptedtext);
    printf("Decryption:      %s\n", decryptedtext);

    free(ciphertext);
    free(decryptedtext);

    return 0;
}

