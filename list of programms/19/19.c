#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef uint64_t block_t;
typedef uint64_t key_t;

void desPermute(block_t *data, const int *perm, int size) {
    block_t result = 0;
    int i;
    for (i = 0; i < size; i++) {
        result |= ((*data >> (64 - perm[i])) & 1) << (size - 1 - i);
    }
    *data = result;
}

void desEncryptBlock(block_t *data, key_t key) {
    *data ^= key;
}

void encryptDES3CBC(block_t *data, key_t key1, key_t key2, key_t key3, block_t iv, size_t numBlocks) {
	int i;
    for (i = 0; i < numBlocks; i++) {
        data[i] ^= iv;
        desEncryptBlock(&data[i], key1);
        desEncryptBlock(&data[i], key2);
        desEncryptBlock(&data[i], key3);
        iv = data[i];
    }
}

int main() {
    key_t key1 = 0x0123456789ABCDEF;
    key_t key2 = 0xFEDCBA9876543210;
    key_t key3 = 0x89ABCDEF01234567;
    block_t iv = 0x0;
    block_t data = 0x0123456789ABCDEF;
    encryptDES3CBC(&data, key1, key2, key3, iv, 1);

    printf("Ciphertext: 0x%016lX\n", data);

    return 0;
}

