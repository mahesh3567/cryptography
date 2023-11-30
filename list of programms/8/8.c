#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generateKey(char keyword[], char key[]) {
    int i, j, k;
    int keywordLength = strlen(keyword);
    char tempKey[26] = {'\0'};
    int index = 0;
    for (i = 0; i < keywordLength; ++i) {
        if (strchr(tempKey, keyword[i]) == NULL) {
            tempKey[index++] = toupper(keyword[i]);
        }
    }
    for (i = 'A'; i <= 'Z'; ++i) {
        if (i != 'J' && strchr(tempKey, i) == NULL) {
            tempKey[index++] = i;
        }
    }
    for (i = 0; i < 26; ++i) {
        key[i] = tempKey[i];
    }
}
void encrypt(char message[], char key[]) {
    int i;

    printf("Encrypted Message: ");
    for (i = 0; message[i] != '\0'; ++i) {
        char ch = message[i];

        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            char encryptedChar = key[ch - base];
            printf("%c", encryptedChar);
        } else {
            printf("%c", ch);
        }
    }

    printf("\n");
}

int main() {
    char keyword[] = "CIPHER";
    char key[26];
    char message[100];
    generateKey(keyword, key);
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    if (message[strlen(message) - 1] == '\n') {
        message[strlen(message) - 1] = '\0';
    }
    encrypt(message, key);
    return 0;
}
