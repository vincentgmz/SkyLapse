# include <ncurses.h>
# include <iostream>
# include <string>
using namespace std;

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
    keypad(stdscr,TRUE);
    int maxX, maxY;

    getmaxyx(stdscr,maxY,maxX); 
    //mvprintw(0,0,"%d",maxY); //y=24
   // mvprintw(1,1,"%d", maxX); //x=80

    int height =16 ;
    int width = 80;
    int starty = 0;
    int startx = 0;

    //create the main game window
    WINDOW* planeWin = createNewWin(height, width, starty, startx, false);

    starty = height;
    height = maxY / 3;

    //create the data window
    WINDOW* dataWin = createNewWin(height, width, starty, startx, true);


    getch();
    endwin();
    return 0;
}

