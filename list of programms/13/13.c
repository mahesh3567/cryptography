#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2
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
    for ( i = 0; i < MATRIX_SIZE; i++) {
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
void hillEncrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *input, char *output) {
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
        multiplyMatrix(key, matrix, result);
        for (j = 0; j < MATRIX_SIZE; j++) {
            output[i + j] = result[j] + 'a';
        }
    }
    output[length] = '\0';
}

int main() {
    char plaintext[] = "ket";
    char ciphertext[] = "mnjhk";
    int key[MATRIX_SIZE][MATRIX_SIZE];
    int matrix[MATRIX_SIZE];
    int result[MATRIX_SIZE];
    int i,j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            matrix[j] = plaintext[i + j] - 'a';
        }
        for (j = 0; j < MATRIX_SIZE; j++) {
            result[j] = ciphertext[i + j] - 'a';
        }

        for ( j = 0; j < MATRIX_SIZE; j++) {
            key[j][i] = result[j];
        }
    }
    int keyInverse[MATRIX_SIZE][MATRIX_SIZE];
    if (!inverse(key, keyInverse)) {
        printf("Error: The key matrix is not invertible\n");
        return 1;
    }
    printf("Key Matrix:\n");
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }
    printf("\nInverse of Key Matrix:\n");
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", keyInverse[i][j]);
        }
        printf("\n");
    }
    printf("\nEncrypting 'hill' with the known key:\n");
    char knownKeyCiphertext[strlen(plaintext) + 1];
    hillEncrypt(key, plaintext, knownKeyCiphertext);
    printf("Ciphertext: %s\n", knownKeyCiphertext);
    printf("\nEncrypting 'hill' with the inverse of the key:\n");
    char inverseKeyCiphertext[strlen(plaintext) + 1];
    hillEncrypt(keyInverse, plaintext, inverseKeyCiphertext);
    printf("Ciphertext: %s\n", inverseKeyCiphertext);

    return 0;
}

