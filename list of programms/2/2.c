#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char message[], char key[]) {
    int i;
    char encryptedMessage[strlen(message)];

    for (i = 0; message[i] != '\0'; ++i) {
        char ch = message[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            encryptedMessage[i] = key[ch - base];
        } else {
            encryptedMessage[i] = ch;
        }
    }

    encryptedMessage[i] = '\0';

    printf("Encrypted Message: %s\n", encryptedMessage);
}

int main() {
    char message[100], key[26];
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the substitution key (26 unique letters): ");
    fgets(key, sizeof(key), stdin);
    if (message[strlen(message) - 1] == '\n') {
        message[strlen(message) - 1] = '\0';
    }
    if (key[strlen(key) - 1] == '\n') {
        key[strlen(key) - 1] = '\0';
    }

    encrypt(message, key);

    return 0; 
}

