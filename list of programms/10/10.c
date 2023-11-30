#include <stdio.h>
#include <string.h>
#include <ctype.h>
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    int i, j;

    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            if (matrix[i][j] == ch || (ch == 'I' && matrix[i][j] == 'J') || (ch == 'J' && matrix[i][j] == 'I')) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char matrix[5][5], char ch1, char ch2) {
    int row1, col1, row2, col2;
    findPosition(matrix, ch1, &row1, &col1);
    findPosition(matrix, ch2, &row2, &col2);
    if (row1 == row2) {
        printf("%c%c", matrix[row1][(col1 + 1) % 5], matrix[row2][(col2 + 1) % 5]);
    }
    else if (col1 == col2) {
        printf("%c%c", matrix[(row1 + 1) % 5][col1], matrix[(row2 + 1) % 5][col2]);
    }
    else {
        printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
    }
}
void playfairEncrypt(char matrix[5][5], char message[]) {
    int i, len;
    for (i = 0, len = strlen(message); i < len; i += 2) {
        char ch1 = toupper(message[i]);
        char ch2 = (i + 1 < len) ? toupper(message[i + 1]) : 'X';

        encryptPair(matrix, ch1, ch2);
    }

    printf("\n");
}

int main() {
    char playfairMatrix[5][5] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'K', 'U', 'N', 'O', 'P'},
        {'Q', 'Z', 'V', 'W', 'X'},
        {'Y', 'E', 'L', 'A', 'R'},
        {'G', 'D', 'S', 'T', 'B'},
        {'C', '\0', '\0', '\0', '\0'} 
    };

    char message[] = "Must see you over Cadogan West. Coming at once";
    playfairEncrypt(playfairMatrix, message);

    return 0;
}

