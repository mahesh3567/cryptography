#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void vigenereEncrypt(char *plaintext, int *key, char *ciphertext) {
    int length = strlen(plaintext);
    int i;
    for (i = 0; i < length; i++) {
        if (plaintext[i] == ' ') {
            ciphertext[i] = ' ';
        } else {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i % length]) % 26) + 'a';
        }
    }
    ciphertext[length] = '\0';
}
void vigenereDecrypt(char *ciphertext, int *key, char *decryptedText) {
    int length = strlen(ciphertext);
    int i;
    for (i = 0; i < length; i++) {
        if (ciphertext[i] == ' ') {
            decryptedText[i] = ' ';
        } else {
            decryptedText[i] = ((ciphertext[i] - 'a' - key[i % length] + 26) % 26) + 'a';
        }
    }
    decryptedText[length] = '\0';
}

int main() {
    char plaintext[] = "send more money";
    int keyStream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[strlen(plaintext) + 1];
    int i;

    vigenereEncrypt(plaintext, keyStream, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);
    char targetText[] = "cash not needed";
    int foundKey[strlen(targetText)];
    for (i = 0; i < strlen(targetText); i++) {
        foundKey[i] = (targetText[i] - 'a' - ciphertext[i] + 26) % 26;
    }
    char decryptedText[strlen(ciphertext) + 1];
    vigenereDecrypt(ciphertext, foundKey, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

