# include <iostream>
# include <ncurses.h>
# include "enemy.hpp"
# include <cstdlib>
using namespace std;

Enemy e1 = {12,78,'*'};
Enemy e2 = {9,70,'*'};
Enemy e3 = {13,57,'*'};
Enemy e4 = {14,30,'*'};
Enemy e5 = {3,28,'*'};
Enemy e6 = {6,10,'*'};


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
void updateEnemyPos(){
  
    
    e1.x--;
    e2.x--;
    e3.x--;
    e4.x--;
    e5.x--;
    e6.x--;
}

void generateEnemy(){
    if (e1.x == 0)
    {
        e1.y = rand()%14+1;
        e1.x = 78;
        e1.shape = '*';
        //e1 = {rand()%14+1,78,'*'};
    }
        if (e2.x == 0)
        {   e2.y = rand()%14+1;
            //e2 = {rand()%14+1,78,'*'};
            e2.x = 78;
            e2.shape = '*';
        }
        if (e3.x == 0)
        {
            e3.y = rand()%14+1;
            e3.x = 78;
            e3.shape = '*';
            //e3 = {rand()%14+1,78,'*'};
        }
        if (e4.x == 0)
        {
            e4.y = rand()%14+1;
            e4.x = 78;
            e4.shape = '*';
            //e4 = {rand()%14+1,78,'*'};
        }
        if (e5.x == 0)
        {
            e5.y = rand()%14+1;
            e5.x = 78;
            e5.shape = '*';
            //e5 = {rand()%14+1,78,'*'};
        }
        if (e6.x == 0)
        {
            e6.y = rand()%14+1;
            e6.x = 78;
            e6.shape = '*';
            //e6 = {rand()%14+1,78,'*'};
        }
      
}
