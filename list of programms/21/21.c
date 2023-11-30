#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef uint64_t block_t;
typedef uint64_t key_t;
typedef uint64_t iv_t;

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

void desDecryptBlock(block_t *data, key_t key) {
    *data ^= key;
}

void encryptECB(block_t *data, key_t key, size_t numBlocks) {
	int i;
    for (i = 0; i < numBlocks; i++) {
        desEncryptBlock(&data[i], key);
    }
}

void encryptCBC(block_t *data, key_t key, iv_t iv, size_t numBlocks) {
	int i;
    for (i = 0; i < numBlocks; i++) {
        data[i] ^= iv;
        desEncryptBlock(&data[i], key);
        iv = data[i];
    }
}

void encryptCFB(block_t *data, key_t key, iv_t iv, size_t numBlocks) {
	int i;
    for (i = 0; i < numBlocks; i++) {
        desEncryptBlock(&iv, key);
        data[i] ^= iv;
        iv = data[i];
    }
}

int main() {
    key_t key = 0x0123456789ABCDEF;
    iv_t iv = 0x0123456789ABCDEF;
    int i;
    block_t data[] = {0x0123456789ABCDEF, 0xFEDCBA9876543210, 0x89ABCDEF01234567};
    size_t numBlocks = sizeof(data) / sizeof(data[0]);

    encryptECB(data, key, numBlocks);

    printf("ECB Ciphertext:\n");
    for (i = 0; i < numBlocks; i++) {
        printf("0x%016lX\n", data[i]);
    }

    memcpy(data, iv, sizeof(iv));
    encryptCBC(&data[1], key, iv, numBlocks - 1);

    printf("\nCBC Ciphertext:\n");
    for (i = 0; i < numBlocks; i++) {
        printf("0x%016lX\n", data[i]);
    }

    memcpy(data, iv, sizeof(iv));
    encryptCFB(&data[1], key, iv, numBlocks - 1);

    printf("\nCFB Ciphertext:\n");
    for (i = 0; i < numBlocks; i++) {
        printf("0x%016lX\n", data[i]);
    }

    return 0;
}

