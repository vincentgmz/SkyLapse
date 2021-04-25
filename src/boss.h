#ifndef BOSS_H
#define BOSS_H
#include <ncurses.h>

#define BOSS_Y_COORDINATE_TOP 5
#define BOSS_Y_COORDINATE_BOTTOM 11
#define BOSS_X_COORDINATE_LEFT 45


using namespace std;

extern int boss_health;

void printBoss(WINDOW* WIN);

#endif