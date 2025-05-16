#ifndef GAME_H
#define GAME_H

#define MAX_DISKS 5
#define TOWERS 3

typedef struct {
    int *disks;       
    int numDisks;
} Tower;

void instructions();
void game(Tower *towers, int n);
void printTowers(Tower *towers);
int movingDisk(Tower *from, Tower *to);
int already_used(int *array, int size, int value);
int is_ordered(Tower *tower, int n);

#endif