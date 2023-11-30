#include <stdio.h>
int modInverse(int a, int m) {
    a = a % m;
    int x;
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
int main() {
    char mostFrequent = 'B';
    char secondMostFrequent = 'U';
    int mostFrequentNum = mostFrequent - 'A';
    int secondMostFrequentNum = secondMostFrequent - 'A';
    int a, b;
    a = (secondMostFrequentNum - mostFrequentNum + 26) % 26;
    b = (mostFrequentNum - a + 26) % 26;
    int aInverse = modInverse(a, 26);
    printf("Key parameters: a = %d, b = %d\n", a, b);
    if (aInverse != -1) {
        printf("Modular inverse of a: %d\n", aInverse);
    } else {
        printf("No modular inverse for a\n");
    }
    return 0;
}
