#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypt(char plaintext, int key) {
    if (isalpha(plaintext)) {
        char base = isupper(plaintext) ? 'A' : 'a';
        return ((plaintext - base + key) % 26) + base;
    } else {
        return plaintext; 
    }
}
void encryptVigenere(const char *plaintext, const int *key, char *ciphertext) {
    size_t text_len = strlen(plaintext);
    int i;
    for (i = 0; i < text_len; ++i) {
        ciphertext[i] = encrypt(plaintext[i], key[i % text_len]);
    }

    ciphertext[text_len] = '\0';
}

int main() {
    const char *plaintext = "HelloWorld";
    const int key[] = {3, 19, 5};

    size_t text_len = strlen(plaintext);
    char *ciphertext = malloc(text_len + 1); 
    if (ciphertext == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;
    }

    encryptVigenere(plaintext, key, ciphertext);

    printf("Plaintext:  %s\n", plaintext);
    printf("Key:        ");
    int i;
    for (i = 0; i < text_len; ++i) {
        printf("%d ", key[i % text_len]);
    }
    printf("\n");
    printf("Ciphertext: %s\n", ciphertext);

    free(ciphertext);

    return 0;
}

