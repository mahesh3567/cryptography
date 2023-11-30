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
void decryptMonoalphabeticSubstitution(const char *ciphertext, const char *mapping, char *plaintext) {
    size_t text_len = strlen(ciphertext);
    int i;
    for (i = 0; i < text_len; ++i) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char decryptedLetter = mapping[ciphertext[i] - base];
            plaintext[i] = decryptedLetter;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }

    plaintext[text_len] = '\0';
}
void monoalphabeticSubstitutionLetterFrequencyAttack(const char *ciphertext, int topPlaintexts) {
    LetterFrequency letterFrequencies[26];
    char mapping[26];
    char plaintext[1000]; 

    int i,j;
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
        int shift = (letterFrequencies[i].letter - 'a' + 22) % 26;

        for (j = 0; j < 26; ++j) {
            mapping[j] = 'a' + (j + shift) % 26;
        }

        decryptMonoalphabeticSubstitution(ciphertext, mapping, plaintext);
        printf("%d. Shift: %d, Plaintext: %s\n", i + 1, shift, plaintext);
    }
}

int main() {
    const char *ciphertext = "Ymj vznhp gwtbs ktc ozruji tajw ymj qfed itl.";
    int topPlaintexts = 5;

    printf("Ciphertext:\n%s\n\n", ciphertext);
    monoalphabeticSubstitutionLetterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

