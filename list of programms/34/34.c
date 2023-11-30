#include <stdio.h>
#include <stdint.h>
#include <string.h>

void xor_bytes(const uint8_t *a, const uint8_t *b, uint8_t *result, size_t len) {
	int i;
    for (i = 0; i < len; ++i) {
        result[i] = a[i] ^ b[i];
    }
}

void round_function(const uint8_t *input, const uint8_t *key, uint8_t *output) {
    xor_bytes(input, key, output, 16);
}
void ecb_encrypt(const uint8_t *plaintext, size_t len, const uint8_t *key, uint8_t *ciphertext) {
	int i;
    for (i = 0; i < len; i += 16) {
        round_function(plaintext + i, key, ciphertext + i);
    }
}
void cbc_encrypt(const uint8_t *plaintext, size_t len, const uint8_t *key, const uint8_t *iv, uint8_t *ciphertext) {
    uint8_t xor_result[16];
    memcpy(xor_result, iv, 16);
    int i;
    for ( i = 0; i < len; i += 16) {
        xor_bytes(plaintext + i, xor_result, ciphertext + i, 16);
        round_function(ciphertext + i, key, xor_result);
    }
}
void cfb_encrypt(const uint8_t *plaintext, size_t len, const uint8_t *key, const uint8_t *iv, uint8_t *ciphertext) {
    uint8_t feedback[16];
    memcpy(feedback, iv, 16);
    int i;
    for (i = 0; i < len; i += 16) {
        round_function(feedback, key, feedback);
        xor_bytes(plaintext + i, feedback, ciphertext + i, 16);
    }
}
void print_hex(const char *label, const uint8_t *data, size_t len) {
    printf("%s: ", label);
    int i;
    for (i = 0; i < len; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    const uint8_t key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x81, 0x5d, 0xc4, 0x2f, 0x35};
    const uint8_t iv[16] = {0x00};

    const char *plaintext = "This is a message for encryption.";
    size_t plaintext_len = strlen(plaintext);

    uint8_t ecb_ciphertext[256];
    uint8_t cbc_ciphertext[256];
    uint8_t cfb_ciphertext[256];
    ecb_encrypt((const uint8_t *)plaintext, plaintext_len, key, ecb_ciphertext);
    print_hex("ECB Ciphertext", ecb_ciphertext, plaintext_len);
    cbc_encrypt((const uint8_t *)plaintext, plaintext_len, key, iv, cbc_ciphertext);
    print_hex("CBC Ciphertext", cbc_ciphertext, plaintext_len);
    cfb_encrypt((const uint8_t *)plaintext, plaintext_len, key, iv, cfb_ciphertext);
    print_hex("CFB Ciphertext", cfb_ciphertext, plaintext_len);

    return 0;
}

