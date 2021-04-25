# include <ncurses.h>
# include <iostream>
# include <string>
# include <unistd.h>
# include "game.h"
# include <ctime>
# include "enemy.h"
# include <cstdlib>
# include <list>
using namespace std;

AREA MAIN_AREA = {0,15,0,79};
AREA INFO_AREA = {16,24,0,80};
Bullet BulletList[MAX_NUM_BULLET];

void CollisionCheck(){

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        for (int j = 0; j < MAX_NUM_ENEMY; j++)
        {
            if (ENEMY_LIST[j].pos.y == BulletList[i].pos.y && BulletList[i].player == true)
            {
                if ((ENEMY_LIST[j].pos.x - BulletList[i].pos.x) / BulletList[i].speed < 1)
                {
                    BulletList[i].exist = false;
                    ENEMY_LIST[j].exist = false;
                }
                
            }   
        }
    }
    
}

void generateBullet(){

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        
        if (BulletList[i].exist == false)
        {
            BulletList[i].exist = true;
            BulletList[i].pos.x = player.pos.x + 1;
            BulletList[i].pos.y = player.pos.y;        
            BulletList[i].symbol = '*';
            BulletList[i].speed = 2;
            BulletList[i].player = true;
            break;
        }

    }
    
}

void printBullet(WINDOW* WIN){

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        
        if (BulletList[i].exist == true)
        {
            mvwaddch(WIN, BulletList[i].pos.y, BulletList[i].pos.x, BulletList[i].symbol);   
        }

    }

}

void updateBullet(){

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {

        if (BulletList[i].exist == true && BulletList[i].player == true)
        {
            BulletList[i].pos.x += BulletList[i].speed;

            if (BulletList[i].pos.x >= MAIN_AREA.right)
            {
                BulletList[i].exist = false;
            }
        }else if (BulletList[i].exist == true && BulletList[i].player == false)
        {
            BulletList[i].pos.x -= BulletList[i].speed;

            if (BulletList[i].pos.x <= MAIN_AREA.left)
            {
                BulletList[i].exist = false;
            }
        }

    }
    
}

void eraseBullet(WINDOW* WIN){

    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        
        if (BulletList[i].exist == true)
        {
            mvwaddch(WIN, BulletList[i].pos.y, BulletList[i].pos.x, ' ');   
        }

    }

}


/* this function creates windows for the main and sub one. 
*/
WINDOW* createNewWin(int height, int width, int starty, int startx, bool isDataWin)
{
    WINDOW* localWin = newwin(height, width, starty, startx);
    box(localWin, 0, 0);
    wrefresh(localWin);

    if (isDataWin == true)
    {
        int score = 0;
        mvwaddstr(localWin, 1, 1, "Score: 0");
        starty += 2;
        startx += 2;
    }

    wrefresh(localWin);
    return localWin;
}


void showTime(int second, WINDOW* win){
   int minute = second / 60;
   second %= 60;
   if (minute/10 == 0)
   {
       if (second / 10== 0){
        mvwprintw(win, 1, 68,"Time: 0%d:0%d",minute,second);
        }
        else{
            mvwprintw(win, 1, 68,"Time: 0%d:%d",minute,second);
        }  
   }
   else{
        if (second / 10== 0){
        mvwprintw(win, 1, 68,"Time: %d:0%d",minute,second);
        }
        else{
            mvwprintw(win, 1, 68,"Time: %d:%d",minute,second);
        }
       
   }
   
   wrefresh(win);
 
}

int main(int argc, char const *argv[])
{
    initscr();
    refresh();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,true);
    nodelay(stdscr,true);
    int maxX, maxY;

    getmaxyx(stdscr,maxY,maxX); 
    //mvprintw(0,0,"%d",maxY); //y=24
   // mvprintw(1,1,"%d", maxX); //x=80

    int height =16;
    int width = 80;
    int starty = 0;
    int startx = 0;

    //create the main game window
    WINDOW* MAIN = createNewWin(height, width, starty, startx, false);

    starty = height;
    height = 8;

    //create the data window
    WINDOW* INFO = createNewWin(height, width, starty, startx, true);
    
    nodelay(INFO,TRUE);
    nodelay(MAIN,TRUE);
    
    //wrefresh(MAIN);
    player.pos.x = 5;
    player.pos.y = 5;
    player.symbol = 'E';




    mvwaddch(MAIN,player.pos.y,player.pos.x,player.symbol);
    

    time_t start = time(NULL);
    srand(time(0));
    bool exit = false;
    int tick = 0;

    for (int i = 0; i < MAX_NUM_ENEMY; i++)
    {
        Enemy* temp = new Enemy;
        temp->exist = false;
        ENEMY_LIST[i] = *temp;

    }
    
    for (int i = 0; i < MAX_NUM_BULLET; i++)
    {
        Bullet* temp = new Bullet;
        temp->exist = false;
        BulletList[i] = *temp;
    }
    
    while (true)
    {   

        usleep(50000);   // Frame rate approximately 50 fps

        time_t now = time(NULL);
        int passed = difftime(now,start);

        char input_key;
        input_key = wgetch(MAIN);
        
       
        switch (input_key)
        {
        case 'w':
            if (player.pos.y > MAIN_AREA.top + 1)
            {
                mvwaddch(MAIN,player.pos.y,player.pos.x,' ');
                player.pos.y -= 1;
            }
            break;
        
        case 's':
            if (player.pos.y < MAIN_AREA.bot - 1)
            {
                mvwaddch(MAIN,player.pos.y,player.pos.x,' ');
                player.pos.y += 1;
            }
            break;
        
        case 'a':
            if (player.pos.x > MAIN_AREA.left + 2)
            {
                mvwaddch(MAIN,player.pos.y,player.pos.x,' ');
                player.pos.x -= 2;
            }
            break;

        case 'd':
            if (player.pos.x < MAIN_AREA.right - 2)
            {
                mvwaddch(MAIN,player.pos.y,player.pos.x,' ');
                player.pos.x += 2;
            }
            break;

        // Space key reflects ' '
        case ' ':
            generateBullet();
            break;
        
        case 'q':
            exit = true;
            break;

        default:
            break;
        }

        eraseEnemy(MAIN);
        eraseBullet(MAIN);

        updateEnemy();
        updateBullet();
        CollisionCheck();
        if (tick % ENEMY_GEN_RATE == 0)
        {
            generateEnemy();
        }
        enemyBullet();
        printEnemy(MAIN);
        printBullet(MAIN);

        if (exit) break;
        mvwaddch(MAIN,player.pos.y,player.pos.x,player.symbol);
        
        wrefresh(MAIN);
        wrefresh(INFO);

        tick++;

        
    }
        
    wrefresh(MAIN);

    

    getch();
    endwin();
    return 0;
}

