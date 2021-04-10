# include <ncurses.h>
# include <iostream>
# include <string>
# include <unistd.h>
# include "game.h"
# include <ctime>
# include "enemy.h"
# include <cstdlib>
using namespace std;

struct
{
    position pos;
    char symbol;
} player;


/*
void printS(int& y,int& x)
{
    int y_pos =y;
    for (int i = 0; i < 4; i++)
    {
        
        mvprintw(y_pos,x+i,"*");
    }
    for (int i = 0; i < 2; i++)
    {
        mvprintw(y_pos,x,"*");
        y_pos++;
        
    }
    for (int i = 0; i <4 ; i++)
    {
        mvprintw(y_pos,x+i,"*");
    }
    for (int i = 0; i < 2; i++)
    {
        mvprintw(y_pos,x+3,"*");
        y_pos++;
        
    }
    for (int i = 0; i < 4; i++)
    {
        mvprintw(y_pos,x+i,"*");
    }
    x += 8;
     
    
}

void printK(int& y, int& x)
{

    for (int i = 0; i < 5; i++)
    {
        mvprintw(y + i, x, "*");
    }
    for (int i = 0; i < 2; i++)
    {
        mvprintw(y + 3 - i, x + 3 * i, "*");
    }
    for (int i = 0; i < 2; i++)
    {
        mvprintw(y + 3 + i, x + 3 * i, "*");
    }
    
    x +=3;
    

}
*/


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
        //printS(starty, startx);
        //printK(starty, startx);


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

void printEnemy(WINDOW* win){

    mvwprintw(win,e1.y,e1.x,"*");
    mvwprintw(win,e2.y,e2.x,"*");
    mvwprintw(win,e3.y,e3.x,"*");
    mvwprintw(win,e4.y,e4.x,"*");
    mvwprintw(win,e5.y,e5.x,"*");
    mvwprintw(win,e6.y,e6.x,"*");  

}

void eraseEnemy(WINDOW* win){
    mvwprintw(win,e1.y,e1.x," ");
    mvwprintw(win,e2.y,e2.x," ");
    mvwprintw(win,e3.y,e3.x," ");
    mvwprintw(win,e4.y,e4.x," ");
    mvwprintw(win,e5.y,e5.x," ");
    mvwprintw(win,e6.y,e6.x," ");  

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

    int height =16 ;
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

    while (true)
    {   
        time_t now = time(NULL);
        int passed = difftime(now,start);
        showTime(passed,INFO);

        
       
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

        case 'q':
            exit = true;
            break;

        default:
            break;
        }
        
        printEnemy(MAIN);

      

        if (exit) break;

        mvwaddch(MAIN,player.pos.y,player.pos.x,player.symbol);
        
        wrefresh(MAIN);
        wrefresh(INFO);


        usleep(20000);

        eraseEnemy(MAIN);

        e1.x--;
        e2.x--;
        e3.x--;
        e4.x--;
        e5.x--;
        e6.x--;
        
        if (e1.x == 0)
        {
            e1 = {rand()%14+1,78,'*'};
        }
        if (e2.x == 0)
        {
            e2 = {rand()%14+1,78,'*'};
        }
        if (e3.x == 0)
        {
            e3 = {rand()%14+1,78,'*'};
        }
        if (e4.x == 0)
        {
            e4 = {rand()%14+1,78,'*'};
        }
        if (e5.x == 0)
        {
            e5 = {rand()%14+1,78,'*'};
        }
        if (e6.x == 0)
        {
            e6 = {rand()%14+1,78,'*'};
        }
      
        
    }
        
    wrefresh(MAIN);

    

    getch();
    endwin();
    return 0;
}

