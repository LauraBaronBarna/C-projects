#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hanoi.h"

int main(int argc, char *argv[]) {
    Tower towers[TOWERS];
    int n;

    instructions();

    if (argc == 2) {
        n = atoi(argv[1]);
        if (n < 1 || n > MAX_DISKS) {
            printf("That's not a valid number of disks. Please choose between 1 and %d.\n", MAX_DISKS);
            return -1;
        }
    } else {
        printf("Type the number of disks you want to play with (minimum 1, maximum %d): ", MAX_DISKS);
        if (scanf("%d", &n) != 1 || n < 1 || n > MAX_DISKS) {
            printf("That's not a valid number of disks. Please choose between 1 and %d.\n", MAX_DISKS);
            return -1;
        }
        while (getchar() != '\n');
    }

    for (int i = 0; i < TOWERS; i++) {

        towers[i].disks = malloc(n * sizeof(int));
        
        if (towers[i].disks == NULL) {
            printf("Memory allocation failed for tower %d.\n", i + 1);
            return -1;
        }
        towers[i].numDisks = 0;
    }

    game(towers, n);
    int playing = 1;
    char input[100]; 
    int actualTower, nextTower;

    while (playing == 1) {
        printTowers(towers);

        printf("Tower number moving from, and tower moving for: \n ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        if (input[0] == 'q' || input[0] == 'Q') {
            printf("Game over.\n");
            break;
        }

        if (sscanf(input, "%d %d", &actualTower, &nextTower) != 2) {
            printf("Try again, you should type two numbers.\n");
            continue;
        }

        if (actualTower < 1 || actualTower > 3 || nextTower < 1 || nextTower > 3) {
            printf("Try again, tower numbers must be between 1 and 3.\n");
            continue;
        }

        if (!movingDisk(&towers[actualTower - 1], &towers[nextTower - 1])) {
            printf("Try again, you can’t place a bigger disk on a smaller one or move from an empty tower.\n");
            continue;
        }

        for (int i = 0; i < TOWERS; i++) {
            if (is_ordered(&towers[i], n)) {
                printTowers(towers);
                printf("Congratulations! You won the game :)\n");
                playing = 0;
                break;
            }
        }
    }

    for (int i = 0; i < TOWERS; i++) {
        free(towers[i].disks);
    }

    return 0;
}