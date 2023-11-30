#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
void decryptWithMapping(const char *ciphertext, const char *mapping, char *plaintext) {
    int length = strlen(ciphertext);
    int i;
    for (i = 0; i < length; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            plaintext[i] = mapping[tolower(ch) - 'a'] + (isupper(ch) ? 'A' : 'a');
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[length] = '\0';
}
void letterFrequencyAttack(const char *ciphertext, int topPlaintexts) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateLetterFrequency(ciphertext, frequency);
    int i,j;
    printf("Letter Frequency in Ciphertext:\n");
    for (i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c: %d\n", 'a' + i, frequency[i]);
    }
    char mapping[ALPHABET_SIZE];
    char defaultMapping[ALPHABET_SIZE] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'u', 'c', 'm', 'f', 'w', 'y', 'p', 'b', 'g', 'v', 'k', 'x', 'q', 'j', 'z'};
    memcpy(mapping, defaultMapping, ALPHABET_SIZE);

    printf("\nPossible Plaintexts:\n");

    for (i = 0; i < topPlaintexts; i++) {
        char plaintext[strlen(ciphertext) + 1];
        decryptWithMapping(ciphertext, mapping, plaintext);

        printf("Mapping %2d: %s\n", i + 1, plaintext);
        char temp = mapping[ALPHABET_SIZE - 1];
        for (j = ALPHABET_SIZE - 1; j > 0; j--) {
            mapping[j] = mapping[j - 1];
        }
        mapping[0] = temp;
    }
}

int main() {
    char ciphertext[] = "Bjmjf wjdwqd Bmn Fbwj, mfqqdum Bmn Fbwj, adwqd Bmn";
    
    int topPlaintexts;
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topPlaintexts);

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

