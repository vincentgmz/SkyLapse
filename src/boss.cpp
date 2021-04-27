#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "boss.h"

using namespace std;

//read the shape of boss in ascii chars
//input: MAIN, location of file to open, y and x coordinate of initial printing position.
void mvw_print_file(WINDOW* WIN,string file_loc, int y, int x){
    
    ifstream fin;
    fin.open(file_loc);
    string str;
    while(getline(fin, str)){
       mvwprintw(WIN,y,x,str.c_str()); 
       y++;
    }
    fin.close();
}

//print boss
//input: the MAIN window
void printBoss(WINDOW* WIN){

    mvw_print_file(WIN, "src/boss.txt", 4, 40);
    
}

//erases boss 
//input:the MAIN window
void cleanBoss(WINDOW* WIN){
    mvw_print_file(WIN,"src/empty.txt",4,40);
}
