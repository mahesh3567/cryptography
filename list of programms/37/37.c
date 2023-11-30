#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char letter;
    int frequency;
} LetterFrequency;

void countLetterFrequencies(const char *text, LetterFrequency *letterFrequencies) {
	int i;
    for (i = 0; i < strlen(text); ++i) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            letterFrequencies[letter - 'a'].frequency++;
        }
    }
}
int compareLetterFrequencies(const void *a, const void *b) {
    return ((LetterFrequency *)b)->frequency - ((LetterFrequency *)a)->frequency;
}
void decryptWithMapping(const char *ciphertext, const char *mapping, char *plaintext) {
	int i;
    for (i = 0; i < strlen(ciphertext); ++i) {
        if (isalpha(ciphertext[i])) {
            char letter = tolower(ciphertext[i]);
            char decryptedLetter = isupper(ciphertext[i]) ? toupper(mapping[letter - 'a']) : mapping[letter - 'a'];
            plaintext[i] = decryptedLetter;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

void letterFrequencyAttack(const char *ciphertext, int topPlaintexts) {
    LetterFrequency letterFrequencies[26];
    char mapping[26];
    int i;
    for (i = 0; i < 26; ++i) {
        letterFrequencies[i].letter = 'a' + i;
        letterFrequencies[i].frequency = 0;
        mapping[i] = 'a' + i;
    }

    countLetterFrequencies(ciphertext, letterFrequencies);

    qsort(letterFrequencies, 26, sizeof(LetterFrequency), compareLetterFrequencies);
    printf("Letter Frequencies in Ciphertext:\n");

    for (i = 0; i < 26; ++i) {
        printf("%c: %d\n", letterFrequencies[i].letter, letterFrequencies[i].frequency);
    }

    printf("\nTop %d Possible Plaintexts:\n", topPlaintexts);
    for (i = 0; i < topPlaintexts; ++i) {
        decryptWithMapping(ciphertext, mapping, mapping);
        printf("%d. %s\n", i + 1, mapping);
    }
}

int main() {
    const char *ciphertext = "Gur dhvpx oebja sbk whzcf bire gur ynml qbt.";

    int topPlaintexts = 5;

    printf("Ciphertext:\n%s\n\n", ciphertext);

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

