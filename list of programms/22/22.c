#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte_t;
typedef uint16_t block_t;

// Key for S-DES
const uint16_t key = 0xFD;

// Initial vector for CBC mode
const uint8_t IV = 0xAA;

// S-DES S-boxes
const uint8_t S_BOX_0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
const uint8_t S_BOX_1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};

// S-DES permutation functions
void applyInitialPermutation(block_t *data) {
    *data = ((*data & 0x80) >> 7) | ((*data & 0x40) >> 3) | ((*data & 0x20) << 1) | ((*data & 0x10) << 5) |
            ((*data & 0x08) << 3) | ((*data & 0x04) << 7) | ((*data & 0x02) >> 1) | ((*data & 0x01) << 3);
}

void applyFinalPermutation(block_t *data) {
    *data = ((*data & 0x80) >> 3) | ((*data & 0x40) << 1) | ((*data & 0x20) >> 5) | ((*data & 0x10) >> 1) |
            ((*data & 0x08) << 3) | ((*data & 0x04) >> 3) | ((*data & 0x02) << 1) | ((*data & 0x01) >> 3);
}

void applyExpansionPermutation(uint8_t *data) {
    *data = ((*data & 0x80) << 4) | ((*data & 0x40) << 1) | ((*data & 0x20) >> 2) | ((*data & 0x10) >> 5) |
            ((*data & 0x08) << 3) | ((*data & 0x04) >> 1) | ((*data & 0x02) << 2) | ((*data & 0x01) << 5);
}

void applyP4Permutation(uint8_t *data) {
    *data = ((*data & 0x08) << 1) | ((*data & 0x04) << 2) | ((*data & 0x02) >> 1) | ((*data & 0x01) >> 2);
}

void applyP8Permutation(uint16_t *data) {
    *data = ((*data & 0x0080) << 4) | ((*data & 0x0040) << 2) | ((*data & 0x0020) << 0) | ((*data & 0x0010) << 2) |
            ((*data & 0x0008) >> 2) | ((*data & 0x0004) << 0) | ((*data & 0x0002) >> 2) | ((*data & 0x0001) >> 0);
}

void applyP10Permutation(uint16_t *data) {
    *data = ((*data & 0x0200) << 5) | ((*data & 0x0100) << 3) | ((*data & 0x0080) << 1) | ((*data & 0x0040) << 4) |
            ((*data & 0x0020) << 2) | ((*data & 0x0010) << 0) | ((*data & 0x0008) << 2) | ((*data & 0x0004) << 0) |
            ((*data & 0x0002) >> 1) | ((*data & 0x0001) >> 3);
}

void applyIPPermutation(block_t *data) {
    *data = ((*data & 0x8000) >> 8) | ((*data & 0x4000) >> 4) | ((*data & 0x2000) >> 0) | ((*data & 0x1000) >> 4) |
            ((*data & 0x0800) >> 0) | ((*data & 0x0400) << 4) | ((*data & 0x0200) << 0) | ((*data & 0x0100) << 4) |
            ((*data & 0x0080) >> 3) | ((*data & 0x0040) << 1) | ((*data & 0x0020) >> 3) | ((*data & 0x0010) << 1) |
            ((*data & 0x0008) >> 3) | ((*data & 0x0004) << 1) | ((*data & 0x0002) >> 3) | ((*data & 0x0001) << 1);
}

void applyInvertedIPPermutation(block_t *data) {
    *data = ((*data & 0x8000) >> 4) | ((*data & 0x4000) >> 0) | ((*data & 0x2000) << 4) | ((*data & 0x1000) << 0) |
            ((*data & 0x0800) >> 4) | ((*data & 0x0400) << 0) | ((*data & 0x0200) >> 4) | ((*data & 0x0100) << 0) |
            ((*data & 0x0080) >> 1) | ((*data & 0x0040) << 3) | ((*data & 0x0020) >> 1) | ((*data & 0x0010) << 3) |
            ((*data & 0x0008) >> 1) | ((*data & 0x0004) << 3) | ((*data & 0x0002) >> 1) | ((*data & 0x0001) << 3);
}

void applySwitchPermutation(block_t *data) {
    *data = ((*data & 0xFF00) >> 8) | ((*data & 0x00FF) << 8);
}

void generateRoundKeys(uint16_t key, uint16_t *k1, uint16_t *k2) {
    uint16_t tempKey;
    applyP10Permutation(&key);

    // Split key into two halves
    uint8_t keyLeft = (key & 0xFF00) >> 8;
    uint8_t keyRight = key & 0x00FF;

    // Circular left shift (LS-1)
    keyLeft = ((keyLeft << 1) & 0xFE) | ((keyLeft & 0x80) >> 7);
    keyRight = ((keyRight << 1) & 0xFE) | ((keyRight & 0x80) >> 7);

    tempKey = ((uint16_t)keyLeft << 8) | keyRight;
    applyP8Permutation(&tempKey);
    *k1 = tempKey;

    // Circular left shift (LS-2)
    keyLeft = ((keyLeft << 2) & 0xFC) | ((keyLeft & 0xC0) >> 6);
    keyRight = ((keyRight << 2) & 0xFC) | ((keyRight & 0xC0) >> 6);

    tempKey = ((uint16_t)keyLeft << 8) | keyRight;
    applyP8Permutation(&tempKey);
    *k2 = tempKey;
}

void encryptSDES(block_t *data, uint16_t key, uint8_t iv) {
    block_t ciphertext = *data;
    generateRoundKeys(key, &key, &key);

    applyInitialPermutation(&ciphertext);
    ciphertext ^= iv;

    // Round 1
    applyExpansionPermutation((uint8_t *)&ciphertext);
    ciphertext ^= key;
    applySBox(&ciphertext);
    applyP4Permutation((uint8_t *)&ciphertext);

    // Round 2
    applySwitchPermutation(&ciphertext);
    applyExpansionPermutation((uint8_t *)&ciphertext);
    ciphertext ^= key;
    applySBox(&ciphertext);
    applyP4Permutation((uint8_t *)&ciphertext);
    applySwitchPermutation(&ciphertext);

    applyInvertedIPPermutation(&ciphertext);
    *data = ciphertext;
}

void decryptSDES(block_t *data, uint16_t key, uint8_t iv) {
    block_t ciphertext = *data;
    generateRoundKeys(key, &key, &key);

    applyInitialPermutation(&ciphertext);
    ciphertext ^= iv;

    // Round 1
    applyExpansionPermutation((uint8_t *)&ciphertext);
    ciphertext ^= key;
    applySBox(&ciphertext);
    applyP4Permutation((uint8_t *)&ciphertext);

    // Round 2
    applySwitchPermutation(&ciphertext);
    applyExpansionPermutation((uint8_t *)&ciphertext);
    ciphertext ^= key;
    applySBox(&ciphertext);
    applyP4Permutation((uint8_t *)&ciphertext);
    applySwitchPermutation(&ciphertext);

    applyInvertedIPPermutation(&ciphertext);
    *data = ciphertext;
}

void applySBox(block_t *data) {
    uint8_t left = (*data & 0xF0) >> 4;
    uint8_t right = *data & 0x0F;

    left = S_BOX_0[(left & 0xC) >> 2][left & 0x3];
    right = S_BOX_1[(right & 0xC) >> 2][right & 0x3];

    *data = ((block_t)left << 4) | right;
}

int main() {
    // Test data
    block_t plaintext = 0b0000000100100011;
    block_t expectedCiphertext = 0b1111010000010110;

    // CBC mode
    uint8_t iv = 0b10101010;
    block_t ciphertext;
    encryptSDES(&plaintext, key, iv);
    ciphertext = plaintext;

    printf("Encrypted Ciphertext: %04X\n", ciphertext);
    printf("Expected Ciphertext:  %04X\n\n", expectedCiphertext);

    decryptSDES(&ciphertext, key, iv);
    printf("Decrypted Plaintext: %04X\n", ciphertext);

    return 0;
}

