#ifndef GAME_H
#define GAME_H

#define ENEMY_GEN_RATE 25
#define MAX_NUM_ENEMY 10
#define MAX_NUM_BULLET 50

struct position
{
    int x;
    int y;
};

struct
{
    position pos;
    char symbol;
} player;

struct Bullet
{
    position pos;
    char symbol;
    bool exist;
    int speed;
};

struct AREA
{

    int top;
    int bot;
    int left;
    int right;

};

extern AREA MAIN_AREA;
extern AREA INFO_AREA;

#endif