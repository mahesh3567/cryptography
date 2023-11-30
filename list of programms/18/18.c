#include <stdio.h>
#include <stdint.h>

typedef uint64_t block_t;
typedef uint64_t key_t;

const int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
                  60, 52, 44, 36, 28, 20, 12, 4,
                  62, 54, 46, 38, 30, 22, 14, 6,
                  64, 56, 48, 40, 32, 24, 16, 8,
                  57, 49, 41, 33, 25, 17, 9, 1,
                  59, 51, 43, 35, 27, 19, 11, 3,
                  61, 53, 45, 37, 29, 21, 13, 5,
                  63, 55, 47, 39, 31, 23, 15, 7};

const int PC1[] = {57, 49, 41, 33, 25, 17, 9,
                   1, 58, 50, 42, 34, 26, 18,
                   10, 2, 59, 51, 43, 35, 27,
                   19, 11, 3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15,
                   7, 62, 54, 46, 38, 30, 22,
                   14, 6, 61, 53, 45, 37, 29,
                   21, 13, 5, 28, 20, 12, 4};

const int PC2[] = {14, 17, 11, 24, 1, 5, 3, 28,
                   15, 6, 21, 10, 23, 19, 12, 4,
                   26, 8, 16, 7, 27, 20, 13, 2,
                   41, 52, 31, 37, 47, 55, 30, 40,
                   51, 45, 33, 48, 44, 49, 39, 56,
                   34, 53, 46, 42, 50, 36, 29, 32};

const int SHIFT_SCHEDULE[] = {1, 1, 2, 2, 2, 2, 2, 2,
                             1, 2, 2, 2, 2, 2, 2, 1};

const int IP_INVERSE[] = {40, 8, 48, 16, 56, 24, 64, 32,
                          39, 7, 47, 15, 55, 23, 63, 31,
                          38, 6, 46, 14, 54, 22, 62, 30,
                          37, 5, 45, 13, 53, 21, 61, 29,
                          36, 4, 44, 12, 52, 20, 60, 28,
                          35, 3, 43, 11, 51, 19, 59, 27,
                          34, 2, 42, 10, 50, 18, 58, 26,
                          33, 1, 41, 9, 49, 17, 57, 25};

block_t initialPermutation(block_t data) {
    block_t result = 0;
    int i;
    for ( i = 0; i < 64; i++) {
        result |= ((data >> (64 - IP[i])) & 1) << (63 - i);
    }
    return result;
}

block_t inverseInitialPermutation(block_t data) {
    block_t result = 0;
    int i;
    for (i = 0; i < 64; i++) {
        result |= ((data >> (64 - IP_INVERSE[i])) & 1) << (63 - i);
    }
    return result;
}

key_t generateKey(key_t key, int round) {
    key_t result = 0;
    int i;
    for (i = 0; i < 56; i++) {
        result |= ((key >> (64 - PC1[i])) & 1) << (55 - i);
    }
    result = ((result << SHIFT_SCHEDULE[round]) | (result >> (28 - SHIFT_SCHEDULE[round]))) & 0xFFFFFFF;
    key_t roundKey = 0;
    for (i = 0; i < 48; i++) {
        roundKey |= ((result >> (56 - PC2[i])) & 1) << (47 - i);
    }
    return roundKey;
}

block_t desDecrypt(block_t data, key_t keys[16]) {
    data = initialPermutation(data);
    uint32_t left = data >> 32;
    uint32_t right = data & 0xFFFFFFFF;
    int round;
    for (round = 15; round >= 0; round--) {
        uint32_t temp = right;
        right = left ^ ((right >> 4) | (right << 28));
        right = right ^ keys[round];
        left = temp;
    }

    block_t result = ((block_t)right << 32) | left;
    result = inverseInitialPermutation(result);

    return result;
}

int main() {
    key_t key = 0x133457799BBCDFF1;
    block_t data = 0x0123456789ABCDEF;
    int i;
    key_t keys[16];
    for (i = 0; i < 16; i++) {
        keys[i] = generateKey(key, i);
    }

    block_t encryptedData = desDecrypt(data, keys);

    printf("Original Data: 0x%016lX\n", data);
    printf("Decrypted Data: 0x%016lX\n", encryptedData);

    return 0;
}

