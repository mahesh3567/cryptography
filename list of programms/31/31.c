#include <stdio.h>

void leftShift(unsigned char *block) {
    int carry = 0;
    int i;
    for (i = 15; i >= 0; --i) {
        int new_carry = (block[i] & 0x80) >> 7;
        block[i] = (block[i] << 1) | carry;
        carry = new_carry;
    }
}
void xorBlocks(const unsigned char *block1, const unsigned char *block2, unsigned char *result) {
	int i;
    for ( i = 0; i < 16; ++i) {
        result[i] = block1[i] ^ block2[i];
    }
}
void generateCMACSubkeys(const unsigned char *key, unsigned char *subkey1, unsigned char *subkey2) {
    unsigned char RB = 0x87;
    unsigned char L[16] = {0};
    unsigned char K1[16], K2[16];
    if ((K1[0] & 0x80) == 0) {
        leftShift(K1);
    } else {
        leftShift(K1);
        xorBlocks(K1, &RB, K1);
    }
    if ((K2[0] & 0x80) == 0) {
        leftShift(K2);
    } else {
        leftShift(K2);
        xorBlocks(K2, &RB, K2);
    }
    memcpy(subkey1, K1, 16);
    memcpy(subkey2, K2, 16);
}

int main() {
    unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x1a, 0x26, 0x2b, 0x1e, 0x7e};
    unsigned char subkey1[16], subkey2[16];
    generateCMACSubkeys(key, subkey1, subkey2);
    printf("Subkey 1: ");
    int i;
    for ( i = 0; i < 16; ++i) {
        printf("%02x", subkey1[i]);
    }
    printf("\n");

    printf("Subkey 2: ");
    for (i = 0; i < 16; ++i) {
        printf("%02x", subkey2[i]);
    }
    printf("\n");

    return 0;
}

