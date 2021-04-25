#include "enemy.h"
#include "game.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

Enemy ENEMY_LIST[MAX_NUM_ENEMY];

void generateEnemy(){

    srand(time(0));
    for (int i = 0; i < MAX_NUM_ENEMY; i++)
    {
        
        if (ENEMY_LIST[i].exist == false){

            ENEMY_LIST[i].exist = true;
            ENEMY_LIST[i].pos.x = MAIN_AREA.right - 1;
            int y_coordinate = rand() % MAIN_AREA.bot;
            while(y_coordinate == 0 || y_coordinate == 15){

                y_coordinate = rand() % MAIN_AREA.bot;

            }
            ENEMY_LIST[i].pos.y = y_coordinate;
            ENEMY_LIST[i].symbol = 'H';
            ENEMY_LIST[i].speed = 1;  // Speed could be adjusted
            break;
        }   
    }

}

void printEnemy(WINDOW* WIN){

    for (int i = 0; i < MAX_NUM_ENEMY; i++)
    {
        
        if (ENEMY_LIST[i].exist == true)
        {

            mvwaddch(WIN, ENEMY_LIST[i].pos.y, ENEMY_LIST[i].pos.x, ENEMY_LIST[i].symbol);            

        }
        
    }
    wrefresh(WIN);
}

void eraseEnemy(WINDOW* WIN){

    for (int i = 0; i < MAX_NUM_ENEMY; i++)
    {
        
        if (ENEMY_LIST[i].exist == true)
        {

            mvwaddch(WIN, ENEMY_LIST[i].pos.y, ENEMY_LIST[i].pos.x, ' ');            

        }
        
    }
    wrefresh(WIN);
}


void updateEnemy(){

    for (int i = 0; i < MAX_NUM_ENEMY; i++)
    {
        if (ENEMY_LIST[i].exist == true)
        {
            ENEMY_LIST[i].pos.x -= ENEMY_LIST[i].speed;
            if (ENEMY_LIST[i].pos.x <= 1)
            {
                ENEMY_LIST[i].exist = false;
            }
            
        }
        
    }

}


