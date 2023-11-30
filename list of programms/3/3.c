#include <stdio.h>
#include <string.h>
#include <ctype.h>

void prepareKeyMatrix(char key[], char keyMatrix[5][5]) {
    int i, j, k;
    int keyLength = strlen(key);
    char tempKey[26] = {'\0'};
    int index = 0;
    for (i = 0; i < keyLength; ++i) {
        if (strchr(tempKey, key[i]) == NULL) {
            tempKey[index++] = key[i];
        }
    }
    for (i = 'A'; i <= 'Z'; ++i) {
        if (i != 'J' && strchr(tempKey, i) == NULL) {
            tempKey[index++] = i;
        }
    }
    k = 0;
    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            keyMatrix[i][j] = tempKey[k++];
        }
    }
}
void findPosition(char keyMatrix[5][5], char ch, int *row, int *col) {
    int i, j;

    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char keyMatrix[5][5], char ch1, char ch2) {
    int row1, col1, row2, col2;
    findPosition(keyMatrix, ch1, &row1, &col1);
    findPosition(keyMatrix, ch2, &row2, &col2);
    if (row1 == row2) {
        printf("%c%c", keyMatrix[row1][(col1 + 1) % 5], keyMatrix[row2][(col2 + 1) % 5]);
    }
    else if (col1 == col2) {
        printf("%c%c", keyMatrix[(row1 + 1) % 5][col1], keyMatrix[(row2 + 1) % 5][col2]);
    }
    else {
        printf("%c%c", keyMatrix[row1][col2], keyMatrix[row2][col1]);
    }
}
void playfairEncrypt(char keyMatrix[5][5], char message[]) {
    int i,j, len;
    len = strlen(message);
    for (i = 0; i < len - 1; i += 2) {
        if (message[i] == message[i + 1]) {
            len++;
            for ( j = len; j > i + 1; j--) {
                message[j] = message[j - 1];
            }
            message[i + 1] = 'X';
        }
    }
    for (i = 0; i < len; i += 2) {
        encryptPair(keyMatrix, message[i], message[i + 1]);
    }

    printf("\n");
}

int main() {
    char key[26];
    char keyMatrix[5][5];
    char message[100];
    printf("Enter the keyword (no repeated letters): ");
    fgets(key, sizeof(key), stdin);
    printf("Enter the message to be encrypted: ");
    fgets(message, sizeof(message), stdin);
    if (key[strlen(key) - 1] == '\n') {
        key[strlen(key) - 1] = '\0';
    }
    if (message[strlen(message) - 1] == '\n') {
        message[strlen(message) - 1] = '\0';
    }
    prepareKeyMatrix(key, keyMatrix);
    playfairEncrypt(keyMatrix, message);

    return 0;
}

