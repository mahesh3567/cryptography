#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
void calculateLetterFrequency(const char *text, int *frequency) {
	int i;
    for (i = 0; i < strlen(text); i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            frequency[tolower(ch) - 'a']++;
        }
    }
}
void decryptWithShift(const char *ciphertext, int shift, char *plaintext) {
    int length = strlen(ciphertext);
    int i;
    for ( i = 0; i < length; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            plaintext[i] = (ch - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[length] = '\0';
}
void letterFrequencyAttack(const char *ciphertext, int topPlaintexts) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateLetterFrequency(ciphertext, frequency);
    int i,shift;
    printf("Letter Frequency in Ciphertext:\n");
    for ( i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %d\n", 'a' + i, frequency[i]);
    }

    printf("\nPossible Plaintexts:\n");

    for (shift = 0; shift < ALPHABET_SIZE; shift++) {
        char plaintext[strlen(ciphertext) + 1];
        decryptWithShift(ciphertext, shift, plaintext);

        printf("Shift %2d: %s\n", shift, plaintext);
    }
}

int main() {
    char ciphertext[] = "Rjmjj Qfjrj nxmjwq Ymfy Htrrj nxm Mfi Ymjwj rdns St mj mjqu. Nx ymj Htrrj nxm Ny. Jtkyqqjr nxmfy yt Xtrj nxm Ymfy.";

    int topPlaintexts;
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topPlaintexts);

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

