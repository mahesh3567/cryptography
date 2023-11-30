#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
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
int determinant(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}
void adjugate(int key[MATRIX_SIZE][MATRIX_SIZE], int adj[MATRIX_SIZE][MATRIX_SIZE]) {
    adj[0][0] = key[1][1];
    adj[0][1] = -key[0][1];
    adj[1][0] = -key[1][0];
    adj[1][1] = key[0][0];
}
int inverse(int key[MATRIX_SIZE][MATRIX_SIZE], int inv[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(key);
    int detInverse = modInverse(det, 26);

    if (det == 0 || detInverse == -1) {
        return 0;
    }

    int adj[MATRIX_SIZE][MATRIX_SIZE];
    adjugate(key, adj);
    int i,j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            inv[i][j] = (adj[i][j] * detInverse) % 26;
        }
    }

    return 1; 
}
void multiplyMatrix(int key[MATRIX_SIZE][MATRIX_SIZE], int message[MATRIX_SIZE], int result[MATRIX_SIZE]) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (j = 0; j < MATRIX_SIZE; j++) {
            result[i] += key[i][j] * message[j];
        }
        result[i] = (result[i] + 26) % 26; 
    }
}
void hillCipher(int key[MATRIX_SIZE][MATRIX_SIZE], char *input, char *output, int encrypt) {
    int length = strlen(input);
    if (length % MATRIX_SIZE != 0) {
        printf("Error: The length of the message must be a multiple of %d\n", MATRIX_SIZE);
        return;
    }

    int matrix[MATRIX_SIZE];
    int result[MATRIX_SIZE];
    int i,j;
    for (i = 0; i < length; i += MATRIX_SIZE) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            matrix[j] = input[i + j] - 'a';
        }
        if (encrypt) {
            multiplyMatrix(key, matrix, result);
        } else {
            int keyInverse[MATRIX_SIZE][MATRIX_SIZE];
            if (!inverse(key, keyInverse)) {
                printf("Error: The key matrix is not invertible\n");
                return;
            }
            multiplyMatrix(keyInverse, matrix, result);
        }
        for (j = 0; j < MATRIX_SIZE; j++) {
            output[i + j] = result[j] + 'a';
        }
    }
    output[length] = '\0';
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {9, 4},
        {5, 7}
    };
    char message[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[strlen(message) + 1];
    hillCipher(key, message, ciphertext, 1);
    printf("Encrypted Message: %s\n", ciphertext);
    char decryptedMessage[strlen(message) + 1];
    hillCipher(key, ciphertext, decryptedMessage, 0);
    printf("Decrypted Message: %s\n", decryptedMessage);

    return 0;
}

