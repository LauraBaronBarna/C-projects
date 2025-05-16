#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hanoi.h"

void instructions() {
    printf("  \n ");
    printf(" Welcome to Hanoi Tower!\n ");
    printf("  \n ");
    printf(" Usage guide: \n ");
    printf("      Your task is to place the disks in increasing order on any tower of your choice.\n ");
    printf("      You win the game when you successfully place the discs in ascending order on one of the towers. \n");
    printf(" \n ");
    printf(" Methods of control: \n");
    printf("       You should type two numbers, the first one to decide from where the disc is moving to, \n");
    printf("       The second one, the destiny of that disk.\n");
    printf("If you want to exit the game, type the letter 'q' from your keyboard.\n");
    printf(" \n ");
}


void game(Tower *towers, int n) {

    int disksVals[MAX_DISKS];
    
    for (int i = 0; i < n; i++) {
        disksVals[i] = i + 1;
    }

    srand(time(NULL));
    int used = 0; 
    while (used < n) {
        int randNum = (rand() % n) + 1; 

        if (!already_used(disksVals, used, randNum)) {
            disksVals[used] = randNum;
            used++;
        }
    }

    towers[0].numDisks = 0;
    for (int i = 0; i < n; i++) {
        towers[0].disks[towers[0].numDisks ++] = disksVals[i];
    }

    for (int i = 1; i < TOWERS; i++) {
        towers[i].numDisks = 0;
    }
}

void printTowers(Tower towers[]) {
    int maxHeight = 0;
    for (int i = 0; i < TOWERS; i++) {
        if (towers[i].numDisks > maxHeight)
            maxHeight = towers[i].numDisks;
    }

    for (int row = maxHeight - 1; row >= 0; row--) {
        for (int t = 0; t < TOWERS; t++) {
            if (row < towers[t].numDisks) {
                int size = towers[t].disks[row];
                for (int s = 0; s < MAX_DISKS - size; s++) printf(" ");
                for (int s = 0; s < size; s++) printf("=");
                printf("|");
                for (int s = 0; s < size; s++) printf("=");
                for (int s = 0; s < MAX_DISKS - size; s++) printf(" ");
            } else {
                for (int s = 0; s < MAX_DISKS; s++) printf(" ");
                printf("|");
                for (int s = 0; s < MAX_DISKS; s++) printf(" ");
            }
            printf("   ");
        }
        printf("\n");
    }

    for (int t = 0; t < TOWERS; t++) {
        for (int s = 0; s < MAX_DISKS * 2 + 1; s++) printf("-");
        printf("   ");
    }
    printf("\n");

    printf("  I. tower       II. tower      III. tower\n\n");
}

int already_used(int *arr, int len, int value) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == value) return 1;
    }
    return 0;
}

int movingDisk(Tower *actualTower, Tower *nextTower) {
    if (actualTower->numDisks == 0) {
        return 0; 
    }

    int disk;
    disk = actualTower->disks[actualTower->numDisks - 1];

    if (nextTower->numDisks > 0 && disk > nextTower->disks[nextTower->numDisks - 1]) {
        return 0;
    }

    nextTower->disks[nextTower->numDisks] = disk;
    nextTower->numDisks = nextTower->numDisks + 1;

    actualTower->numDisks = actualTower->numDisks - 1;

    return 1; 
}

int is_ordered(Tower *tower, int n) {
    if (tower->numDisks != n) {
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        if (tower->disks[i] < tower->disks[i + 1]) {
            return 0;
        }
    }
    return 1;
}