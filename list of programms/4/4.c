#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereEncrypt(char message[], char key[]) {
    int i, j;
    int messageLength = strlen(message);
    int keyLength = strlen(key);

    for (i = 0, j = 0; i < messageLength; ++i) {
        char ch = message[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            char keyChar = toupper(key[j % keyLength]); 
            char encryptedChar = ((ch - base) + (keyChar - 'A')) % 26 + base;
            printf("%c", encryptedChar);
            ++j;
        } else {
            printf("%c", ch);
        }
    }

    printf("\n");
}

int main() {
    char message[100], key[100];
    printf("Enter the message to be encrypted: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    if (message[strlen(message) - 1] == '\n') {
        message[strlen(message) - 1] = '\0';
    }
    if (key[strlen(key) - 1] == '\n') {
        key[strlen(key) - 1] = '\0';
    }
    printf("Encrypted Message: ");
    vigenereEncrypt(message, key);

    return 0;
}

