#include <stdio.h>
#include <string.h> // Include the header file for string functions

int main() {
    char alpha[100] = "abcdefghijklmnopqrstuvwxyz", key[100] = "zyxwvutsrqponmlkjihgfedcba", plain[100], cipher[100];
    int m = 0, index[100];

    printf("Enter plain text: ");
    scanf("%s", plain);

    // Use strlen from string.h to get the length of the input string
    for (int i = 0; i < strlen(plain); i++) {
        for (int j = 0; j < strlen(alpha); j++) {
            if (plain[i] == alpha[j]) {
                index[m] = j;
                m++;
            }
        }
    }

    printf("Cipher text: ");
    for (int i = 0; i < strlen(plain); i++) {
        cipher[i] = key[index[i]];
        printf("%c", cipher[i]);
    }
    printf("\nPlain text: ");
    for (int i = 0; i < strlen(plain); i++) {
        plain[i] = alpha[index[i]];
        printf("%c", plain[i]);
    }

    return 0; // Return 0 to indicate successful execution
}

