#include "game.h"
#include <ncurses.h>

#ifndef ENEMY_H
#define ENEMY_H

struct Enemy
{
    position pos;
    char symbol;
    int speed;
    bool exist;
};

extern Enemy ENEMY_LIST[MAX_NUM_ENEMY];

void generateEnemy();
void printEnemy(WINDOW* WIN);
void eraseEnemy(WINDOW* WIN);
void updateEnemy();
void enemyBullet();

#endif









