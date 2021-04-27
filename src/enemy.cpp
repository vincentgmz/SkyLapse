#include "enemy.h"
#include "game.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

Enemy ENEMY_LIST[MAX_NUM_ENEMY];


// This cpp file is about creating,printing, erasing,updating enemies and creating their bullets
//generates Enemy randomly
void generateEnemy(){


    srand(time(0));
    for (int i = 0; i < MAX_NUM_ENEMY; i++)
    {
        
        if (ENEMY_LIST[i].exist == false){

            ENEMY_LIST[i].exist = true;
            ENEMY_LIST[i].pos.x = MAIN_AREA.right - 1; 
            int y_coordinate = rand() % (MAIN_AREA.bot - 3) + 2;
            while(y_coordinate == 0 || y_coordinate == 15){ //regenerate y-coordinate if it overlaps with 
                                                            //the top and bottom of the main window

                y_coordinate = rand() % MAIN_AREA.bot;

            }
            ENEMY_LIST[i].pos.y = y_coordinate;
            ENEMY_LIST[i].symbol = 'H';
            ENEMY_LIST[i].speed = 1;  // Speed could be adjusted
            break;
        }   
    }

}

//prints enemy
// input: the MAIN window
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

//erases enemy
// input: the MAIN window
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



//updates enemies' positions, whether they are alive or dead , and their effects to base_health
void updateEnemy(){


 for (int i = 0; i < MAX_NUM_ENEMY; i++)
    {
        if (ENEMY_LIST[i].exist == true)
        {
            ENEMY_LIST[i].pos.x -= ENEMY_LIST[i].speed;
            if (ENEMY_LIST[i].pos.x <= 1)
            {
                base_health -= 1;
                ENEMY_LIST[i].exist = false;
            }
            
        }
        
    }

}

//create enemy bullets denoted as '*' for each enemy. 
void enemyBullet(){

    for (int i = 0; i < MAX_NUM_ENEMY; i++)
    {
        if (ENEMY_LIST[i].exist == true)
        {
            
            int random_number = rand() % ENEMY_BULLET_GEN_RATE;
            if (random_number == 1)  
            {
                for (int j = 0; j < MAX_NUM_BULLET; j++)
                {
                    if (BulletList[j].exist == false){
                        BulletList[j].exist = true;
                        BulletList[j].player = false;
                        BulletList[j].pos.x = ENEMY_LIST[i].pos.x - 1;
                        BulletList[j].pos.y = ENEMY_LIST[i].pos.y;
                        BulletList[j].symbol = '*';
                        BulletList[j].speed = 2;
                        break;
                    }

                }
               
            }
        }
        

    }
    
}




