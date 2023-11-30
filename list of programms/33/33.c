#include <stdio.h>
#include <stdint.h>

uint64_t permute(uint64_t input, const int *table, int table_size) {
    uint64_t result = 0;
    int i;
    for (i = 0; i < table_size; ++i) {
        int bit_position = table[i] - 1; 
        result |= ((input >> bit_position) & 1) << i;
    }
    return result;
}

uint32_t customSubstitution(uint32_t input) {
    return input;
}

uint32_t roundFunction(uint32_t right, uint64_t subkey) {
    uint64_t expanded = permute((uint64_t)right, (const int[]){32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1}, 48);

    expanded ^= subkey;

    uint32_t sbox_output = customSubstitution((uint32_t)expanded);

    return (uint32_t)permute((uint64_t)sbox_output, (const int[]){16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25}, 32);
}

void encryptDES(const uint64_t plaintext, const uint64_t key, uint64_t *ciphertext) {
    uint64_t permuted = permute(plaintext, (const int[]){58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7}, 64);

    uint64_t key_permuted = permute(key, (const int[]){57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4}, 56);


    uint32_t key_left = key_permuted >> 28;
    uint32_t key_right = key_permuted & 0xFFFFFFF;
    int i;
    for ( i = 0; i < 16; ++i) {
        uint32_t subkey = (key_left << i) | (key_right >> (28 - i));

        uint32_t right = (uint32_t)permuted;
        uint32_t left = (uint32_t)(permuted >> 32);
        uint32_t new_right = left ^ roundFunction(right, subkey);
        uint32_t new_left = right;

        permuted = ((uint64_t)new_left << 32) | new_right;
    }

    *ciphertext = permute(permuted, (const int[]){40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25}, 64);
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t ciphertext;

    encryptDES(plaintext, key, &ciphertext);

    printf("Plaintext: 0x%016llx\n", plaintext);
    printf("Key: 0x%016llx\n", key);
    printf("Ciphertext: 0x%016llx\n", ciphertext);

    return 0;
}

