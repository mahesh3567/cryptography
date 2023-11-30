#include <stdio.h>
#include <string.h>

#define AES_BLOCK_SIZE 16

void xorBlocks(const unsigned char *block1, const unsigned char *block2, unsigned char *result) {
	int i;
    for (i = 0; i < AES_BLOCK_SIZE; ++i) {
        result[i] = block1[i] ^ block2[i];
    }
}
void aes_cbc_encrypt(const unsigned char *plaintext, unsigned char *ciphertext,
                     const unsigned char *key, const unsigned char *iv){
					 }

void cbc_mac_one_block(const unsigned char *message, const unsigned char *key, const unsigned char *iv,
                       unsigned char *mac) {
    unsigned char block[AES_BLOCK_SIZE];
    memcpy(block, message, AES_BLOCK_SIZE);
    int i;
    for (i = 0; i < AES_BLOCK_SIZE; ++i) {
        block[i] ^= iv[i];
    }

    aes_cbc_encrypt(block, mac, key, iv);
}

int main() {
    unsigned char key[AES_BLOCK_SIZE] = "0123456789abcdef";
    unsigned char iv[AES_BLOCK_SIZE] = "aaaaaaaaaaaaaaaa";
    unsigned char message[AES_BLOCK_SIZE] = "Hello1234567890";
    unsigned char mac[AES_BLOCK_SIZE];
    cbc_mac_one_block(message, key, iv, mac);

    unsigned char two_block_message[AES_BLOCK_SIZE * 2];
    memcpy(two_block_message, message, AES_BLOCK_SIZE);

    unsigned char xor_result[AES_BLOCK_SIZE];
    xorBlocks(message, mac, xor_result);
    memcpy(two_block_message + AES_BLOCK_SIZE, xor_result, AES_BLOCK_SIZE);
    unsigned char two_block_mac[AES_BLOCK_SIZE];
    cbc_mac_one_block(two_block_message, key, iv, two_block_mac);
    printf("One-block CBC-MAC: ");
    int i;
    for (i = 0; i < AES_BLOCK_SIZE; ++i) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    printf("CBC-MAC for X || (X XOR T): ");
    for (i = 0; i < AES_BLOCK_SIZE; ++i) {
        printf("%02x", two_block_mac[i]);
    }
    printf("\n");

    return 0;
}

