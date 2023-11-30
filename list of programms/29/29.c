#include <stdio.h>
#include <stdint.h>

#define WIDTH 1600
#define CAPACITY 512
void printState(const uint64_t state[5][5]) {
	int i,j;
    for ( i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%016lx ", state[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int allNonzero(const uint64_t state[5][5]) {
	int i,j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (j < 2 && state[i][j] == 0) {
                return 0; 
            }
        }
    }
    return 1;
}

int main() {
    uint64_t state[5][5] = {{0}};
    printf("Initial State:\n");
    printState(state);
    int iteration = 0;
    int i,j;
    while (!allNonzero(state)) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 2; j++) {
                state[i][j] += iteration;
            }
        }
        printf("After Iteration %d:\n", iteration + 1);
        printState(state);
        iteration++;
    }

    printf("All lanes in the capacity portion have at least one nonzero bit after %d iterations.\n", iteration);

    return 0;
}

