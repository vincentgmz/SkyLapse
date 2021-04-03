# include <ncurses.h>
# include <iostream>
# include <string>
# include <unistd.h>
# include "game.h"
using namespace std;

struct
{
    position pos;
    char symbol;
} player;


struct 
{

    int top;
    int bot;
    int left;
    int right;

} MAIN_AREA;

struct 
{
    int top;
    int bot;
    int left;
    int right;

} INFO_AREA;



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
        mvprintw(starty+1, startx+2, "Score: %d",score);
        mvprintw(starty+1, startx+68,"Time: 00:00");
        starty += 2;
        startx += 2;
        //printS(starty, startx);
        //printK(starty, startx);


    }

    wrefresh(localWin);
    return localWin;
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
    WINDOW* main = createNewWin(height, width, starty, startx, false);

    starty = height;
    height = maxY / 3;

    //create the data window
    WINDOW* info = createNewWin(height, width, starty, startx, true);

    wrefresh(main);
    MAIN_AREA = {0,16,0,80};
    INFO_AREA = {16,24,0,80};

    player.pos.x = 5;
    player.pos.y = 5;
    player.symbol = 'E';

    mvwaddch(main,player.pos.y,player.pos.x,player.symbol);
    
    
    bool exit = false;
    while (true)
    {
        
        char input_key;
        input_key = wgetch(main);

        switch (input_key)
        {
        case 'w':
            if (player.pos.y > MAIN_AREA.top)
            {
                mvwaddch(main,player.pos.y,player.pos.x,' ');
                player.pos.y -= 1;
            }
            break;
        
        case 's':
            if (player.pos.y < MAIN_AREA.bot)
            {
                mvwaddch(main,player.pos.y,player.pos.x,' ');
                player.pos.y += 1;
            }
            break;
        
        case 'a':
            if (player.pos.x > MAIN_AREA.left)
            {
                mvwaddch(main,player.pos.y,player.pos.x,' ');
                player.pos.x -= 1;
            }
            break;

        case 'd':
            if (player.pos.x < MAIN_AREA.right)
            {
                mvwaddch(main,player.pos.y,player.pos.x,' ');
                player.pos.x += 1;
            }
            break;

        case 'q':
            exit = true;
            break;

        default:
            break;
        }

        if (exit)
        {
            break;
        }

        mvwaddch(main,player.pos.y,player.pos.x,player.symbol);
        
        wrefresh(main);

        usleep(10000);

    }
        
    wrefresh(main);
    

    getch();
    endwin();
    return 0;
}

