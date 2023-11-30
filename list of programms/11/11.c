#include <stdio.h>
#include <math.h>

int main() {
    int matrixSize = 25;
    int charactersPerElement = 26; 
    long long totalKeys = pow(charactersPerElement, matrixSize);

    printf("Total possible keys without considering repeated encryption results: %lld\n", totalKeys);

    return 0;
}

