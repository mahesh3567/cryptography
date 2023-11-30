#include <stdio.h>
#include <string.h>

void encrypt(char message[], int key) {
    int i;
    char encryptedMessage[strlen(message)];

    for (i = 0; message[i] != '\0'; ++i) {
        char ch = message[i];

        if (ch >= 'a' && ch <= 'z') {
            encryptedMessage[i] = 'a' + (ch - 'a' + key) % 26;
        } else if (ch >= 'A' && ch <= 'Z') {
            encryptedMessage[i] = 'A' + (ch - 'A' + key) % 26;
        } else {
            encryptedMessage[i] = ch;
        }
    }
    encryptedMessage[i] = '\0';
    printf("Encrypted Message: %s\n", encryptedMessage);
}
int main() {
    char message[100];
    int key;
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the key (shift value): ");
    scanf("%d", &key);
    if (key < 1 || key > 25) {
        printf("Invalid key. Key should be in the range 1 to 25.\n");
        return 1; 
    }
    if (message[strlen(message) - 1] == '\n') {
        message[strlen(message) - 1] = '\0';
    }
    encrypt(message, key);
    return 0; 
}

